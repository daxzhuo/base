#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
using namespace std;
struct Node {
  list<int> keys; // save the key that have the same freqency
  int count;
  Node *prev;
  Node *next;
  Node() : count(0), prev(nullptr), next(nullptr) {}
};

class LFUCache {
public:
  LFUCache(int capacity) : cap(capacity) {
    freq.next = &freq;
    freq.prev = &freq;
  }

  void insertNode(Node *handle, Node *newNode) {
    newNode->next = handle->next;
    newNode->prev = handle;
    handle->next->prev = newNode;
    handle->next = newNode;
  }

  void removeNode(Node *handle) {
    handle->next->prev = handle->prev;
    handle->prev->next = handle->next;
    delete handle;
  }

  void increaseCount(int key) {
    Node *handle = &freq;
    list<int>::iterator it;
    if (maps.find(key) != maps.end()) {
      handle = fmaps[key];
      it = lmaps[key];
      handle->keys.erase(it);
    }
    if (handle->next->count != handle->count + 1) {
      Node* newNode = new Node();
      newNode->count = handle->count + 1;
      insertNode(handle, newNode);
    }
    fmaps[key] = handle->next;
    handle->next->keys.push_back(key);
    lmaps[key] = --handle->next->keys.end();
    if (handle != &freq && handle->keys.size() == 0) {
      removeNode(handle);
    }
  }

  int get(int key) {
    if (maps.find(key) == maps.end()) {
      return -1;
    }
    increaseCount(key);
    return maps[key];
  }

  void set(int key, int value) {
    if (cap == 0)
      return;
    if (maps.find(key) == maps.end() && maps.size() == cap) {
      int old = freq.next->keys.front();
      cout << "invalid " << old << endl;
      freq.next->keys.pop_front();
      fmaps.erase(old);
      maps.erase(old);
      lmaps.erase(old);
      if (freq.next->keys.size() == 0)
        removeNode(freq.next);
    }
    increaseCount(key);
    maps[key] = value;
  }

private:
  int cap;
  unordered_map<int, Node*> fmaps;
  unordered_map<int, int> maps;
  unordered_map<int, list<int>::iterator> lmaps;
  Node freq; // freq.prev have most freq, freq.next have least freq
};

int main() {

  LFUCache *cache = new LFUCache(2 /* capacity */);

  cache->set(2, 1);
  cache->set(1, 1);
  cout << cache->get(1) << endl; // returns 1
  cache->set(2, 3);              // evicts key 2
  cout << cache->get(1) << endl; // returns -1 (not found)
  cout << cache->get(3) << endl; // returns 3->
  cache->set(4, 1);              // evicts key 1->
  cout << cache->get(1) << endl; // returns -1 (not found)
  cout << cache->get(2) << endl; // returns 3
  cout << cache->get(4) << endl; // returns 4
}
