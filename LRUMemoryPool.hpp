//
// Created by Cristiano on 2022/6/3.
//

#ifndef BPLUSTREE_LRUMEMORYPOOL_HPP
#define BPLUSTREE_LRUMEMORYPOOL_HPP
#include <iostream>
#include <fstream>
#include "hashmap.hpp"
using std::string;

namespace Geneva {
    template<class T, class preface = int>
    class MemoryPool {
    private:
        class List {
        public:
            class Node {
            public:
                int key = -1;
                T *value = nullptr;
                Node *pre = nullptr,*next = nullptr;
                bool updated = false;

                Node() = default;

                Node(int k, const T &t, Node *pre_ = nullptr, Node *nxt_ = nullptr) : key(k), value(new T(t)), pre(pre_),
                                                                                      next(nxt_) {}

                ~Node() {
                    delete value;
                }
            };

            Node *head = nullptr, *tail = nullptr;
            int listSize = 0;
            int capacity = 0;

            explicit List(int _capacity) : capacity(_capacity) {
                head = new Node(), tail = new Node();
                head->next = tail, tail->pre = head;
            }

            ~List() {
                Node *tmp = head;
                while (head != nullptr) {
                    head = head->next;
                    delete tmp;
                    tmp = head;
                }
            }

            void clear() {
                listSize = 0;
                Node *tmp = head;
                while (head != nullptr) {
                    head = head->next;
                    delete tmp;
                    tmp = head;
                }
                head = new Node(), tail = new Node();
                head->next = tail, tail->pre = head;
            }

            void push_front(Node *n) {
                head->next->pre = n;
                n->next = head->next;
                head->next = n;
                n->pre = head;
                listSize++;
            }

            void pop_to_front(Node *n) {
                n->pre->next = n->next;
                n->next->pre = n->pre;
                listSize--;
                push_front(n);
            }

            Node *pop_back() {
                Node *tmp = tail->pre;
                tmp->pre->next = tail;
                tail->pre = tail->pre->pre;
                listSize--;
                return tmp;
            }

            void erase(Node *n) {
                n->pre->next = n->next;
                n->next->pre = n->pre;
                listSize--;
                delete n;
            }

            bool full() const {
                return listSize == capacity;
            }
        };

        using node_t = typename List::Node;
        FILE *file;
        const string filename;
        int writePoint=-1;
        
        HashMap2<int, node_t*> hashmap;
        List cache;

        int count_cache(int key) {
            return hashmap.count(key);
        }


        void erase_cache(int key) {
            cache.erase(hashmap[key]);
            hashmap.erase(key);
        }

        void write_cache(int key, const T &o) {
            if (count_cache(key)) {
                cache.pop_to_front(hashmap[key]);
                *hashmap[key]->value = o;
                return;
            }
            auto newNode = new node_t(key, o);
            if (cache.full())refresh();
            cache.push_front(newNode);
            hashmap[key] = newNode;
        }

        void refresh() {
            node_t *tmp = cache.pop_back();
            hashmap.erase(tmp->key);
            if (tmp->updated)update_file(tmp->key, *tmp->value);
            delete tmp;
        }
        int write_file(const T &o) {
            int offset;
            file = fopen(filename.c_str(), "rb+");
            if (writePoint <= 0) {
                fseek(file, 0, 2);
                offset = ftell(file);
            } else {
                offset = writePoint;
                fseek(file, writePoint, 0);
                fread(reinterpret_cast<char *>(&writePoint), sizeof(int), 1, file);
                fseek(file, sizeof(preface), 0);
                fwrite(reinterpret_cast<const char *>(&writePoint), sizeof(int), 1, file);
                fseek(file, offset, 0);
            }
            fwrite(reinterpret_cast<const char *>(&o), sizeof(T), 1, file);
            fclose(file);
            return offset;
        }

        T read_file(int offset) {
            file = fopen(filename.c_str(), "rb");
            T tmp;
            fseek(file, offset, 0);
            fread(reinterpret_cast<char *>(&tmp), sizeof(T), 1, file);
            fclose(file);
            return tmp;
        }

        void update_file(int offset, const T &o) {
            file = fopen(filename.c_str(), "rb+");
            fseek(file, offset, 0);
            fwrite(reinterpret_cast<const char *>(&o), sizeof(T), 1, file);
            fclose(file);
        }

        void erase_file(int offset) {
            file = fopen(filename.c_str(), "rb+");
            fseek(file, offset, 0);
            fwrite(reinterpret_cast<const char *>(&writePoint), sizeof(int), 1, file);
            writePoint = offset;
            fseek(file, sizeof(preface), 0);
            fwrite(reinterpret_cast<const char *>(&writePoint), sizeof(int), 1, file);
            fclose(file);
        }

    public:
        explicit MemoryPool(const string &_filename, const preface &pre = preface{}, int _capacity = 120)
                : filename(_filename), cache(_capacity), hashmap() {
            file = fopen(filename.c_str(), "rb");
            if (file == NULL) {
                file = fopen(filename.c_str(), "wb+");
                fclose(file);
                writePoint = -1;
                preface tmp(pre);
                file = fopen(filename.c_str(), "rb+");
                fseek(file, 0, 0);
                fwrite(reinterpret_cast<const char *>(&tmp), sizeof(preface), 1, file);
                fseek(file, sizeof(preface), 0);
                fwrite(reinterpret_cast<const char *>(&writePoint), sizeof(int), 1, file);
                fclose(file);
            } else {
                fseek(file, sizeof(preface), 0);
                fread(reinterpret_cast<char *>(&writePoint), sizeof(int), 1, file);
                fclose(file);
            }
        }

        ~MemoryPool() {
            node_t *now = cache.head->next;
            while (now != cache.tail) {
                if (now->updated)update_file(now->key, *now->value);
                now = now->next;
            }
        }

        T read(int offset) {
            T tmp = count_cache(offset) ? *hashmap[offset]->value : read_file(offset);
            write_cache(offset, tmp);
            return tmp;
        }

        int write(const T &o) {
            int offset = write_file(o);
            write_cache(offset, o);
            return offset;
        }

        void update(const T &o, int offset) {
            write_cache(offset, o);
            hashmap[offset]->updated = true;
        }

        void erase(int offset) {
            if (count_cache(offset))erase_cache(offset);
            erase_file(offset);
        }

        void clear(preface pre = preface{}) {
            hashmap.clear();
            cache.clear();
            file = fopen(filename.c_str(), "wb+");
            fclose(file);
            writePoint = -1;
            preface tmp(pre);
            file = fopen(filename.c_str(), "rb+");
            fseek(file, 0, 0);
            fwrite(reinterpret_cast<const char *>(&tmp), sizeof(preface), 1, file);
            fseek(file, sizeof(preface), 0);
            fwrite(reinterpret_cast<const char *>(&writePoint), sizeof(int), 1, file);
            fclose(file);
        }

        preface readPre() {
            file = fopen(filename.c_str(), "rb+");
            fseek(file, 0, 0);
            preface tmp;
            fread(reinterpret_cast<char *>(&tmp), sizeof(preface), 1, file);
            fclose(file);
            return tmp;
        }

        void updatePre(const preface &o) {
            file = fopen(filename.c_str(), "rb+");
            fseek(file, 0, 0);
            fwrite(reinterpret_cast<const char *>(&o), sizeof(preface), 1, file);
            fclose(file);
        }

        int getWritePoint() {
            if (writePoint >= 0)return writePoint;
            else {
                file = fopen(filename.c_str(), "rb+");
                fseek(file, 0, 2);
                int tmpWritePoint = ftell(file);
                fclose(file);
                return tmpWritePoint;
            }
        }
    };
}
#endif //BPLUSTREE_LRUMEMORYPOOL_HPP
