#ifndef ESTL_TREE_HPP_
#define ESTL_TREE_HPP_

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace estl {
namespace tree {
  template <typename _Tp, typename _Al = std::allocator<_Tp>>
  class Tree {
   public:
    class depth_iterator {
     public:
      depth_iterator() {}
      depth_iterator(Tree<_Tp, _Al>* node) : node_(node) {}

      _Tp& operator*() const { return node_->node; }
      _Tp* operator->() const { return &(node_->node); }

      bool operator==(const depth_iterator& rhs) const {
        if (rhs.node_ == node_) {
          return true;
        } else {
          return false;
        }
      }
      bool operator!=(const depth_iterator& rhs) const {
        if (rhs.node_ != node_) {
          return true;
        } else {
          return false;
        }
      }
      depth_iterator& operator++() {
        if (node_ == nullptr) {
          throw std::logic_error("Tree iterator node is uninitialized");
        }
        if (node_->size() != 0) {
          node_ = node_->begin().node_;
        } else {
          while (node_->next_ == nullptr) {
            node_ = node_->parent_;
            if (node_ == nullptr) return *this;
          }
          node_ = node_->next_;
        }
        return *this;
      }
      depth_iterator& operator--() {
        if(node_ == nullptr){
          throw std::logic_error("Tree iterator node in uninitialized");
        }
        if(node_->prev_ != nullptr){
          node_ = node_->prev_;
          while(node_->end() != nullptr){
            node_ = node_->end().node_;
          }
        }else{
          node_ = node_->parent_;
        }
        return *this;
      }
      depth_iterator& operator+=(unsigned n) {
        while(n > 0){
          ++(*this);
          --n;
        }
        return *this;
      }
      depth_iterator& operator-=(unsigned n) {
        while(n > 0){
          --(*this);
          --n;
        }
        return *this;
      }
      Tree<_Tp, _Al>* node_;
    };

    typedef _Al allocator_type;
    typedef typename _Al::value_type value_type;
    typedef Tree<_Tp, _Al>& reference;
    typedef const Tree<_Tp, _Al>& const_reference;
    typedef typename std::vector<Tree<_Tp, _Al>>::reference child_reference;
    typedef typename std::vector<Tree<_Tp, _Al>>::const_reference
        const_child_reference;
    typedef typename _Al::difference_type difference_type;
    typedef typename _Al::size_type size_type;
    typedef typename _Al::pointer pointer;
    typedef typename _Al::const_pointer const_pointer;
    typedef depth_iterator iterator;
    typedef const depth_iterator const_iterator;
    typedef typename std::vector<Tree<_Tp, _Al>>::iterator child_iterator;
    typedef typename std::vector<Tree<_Tp, _Al>>::const_iterator
        const_child_iterator;
    typedef typename std::vector<Tree<_Tp, _Al>>::reverse_iterator
        reverse_child_iterator;
    typedef typename std::vector<Tree<_Tp, _Al>>::const_reverse_iterator
        const_reverse_child_iterator;

    Tree() : node(_Tp()), parent_(nullptr), prev_(nullptr), next_(nullptr) {}
    Tree(const _Tp& val)
        : node(val), parent_(nullptr), prev_(nullptr), next_(nullptr) {}
    Tree(_Tp&& val)
        : node(val), parent_(nullptr), prev_(nullptr), next_(nullptr) {}
    Tree(const _Tp& val, Tree<_Tp, _Al>* parent)
        : node(val), parent_(parent), prev_(nullptr), next_(nullptr) {}
    Tree(_Tp&& val, Tree<_Tp, _Al>* parent)
        : node(val), parent_(parent), prev_(nullptr), next_(nullptr) {}
    Tree(const _Tp& val, Tree<_Tp, _Al>* parent, Tree<_Tp, _Al>* prev,
         Tree<_Tp, _Al>* next)
        : node(val), parent_(parent), prev_(prev), next_(next) {}
    Tree(_Tp&& val, Tree<_Tp, _Al>* parent, Tree<_Tp, _Al>* prev,
         Tree<_Tp, _Al>* next)
        : node(val), parent_(parent), prev_(prev), next_(next) {}
    Tree(const Tree<_Tp, _Al>& copy)
        : node(copy.node), children_(copy.children_) {}
    ~Tree() {}

    Tree<_Tp, _Al>& operator=(const _Tp& val) {
      node = val;
      return *this;
    }
    Tree<_Tp, _Al>& operator=(const Tree<_Tp, _Al>& copy) {
      node = copy.node;
      children_ = copy.children_;
      return *this;
    }

    Tree<_Tp, _Al> get_parent() { return *parent_; }
    Tree<_Tp, _Al>* get_parent_ptr() { return parent_; }
    Tree<_Tp, _Al> get_next() { return *next_; }
    Tree<_Tp, _Al>* get_next_ptr() { return next_; }
    Tree<_Tp, _Al> get_prev() { return *prev_; }
    Tree<_Tp, _Al>* get_prev_ptr() { return prev_; }

    void set_parent(Tree<_Tp, _Al> parent) { parent_ = &parent; }
    void set_parent(Tree<_Tp, _Al>* parent) { parent_ = parent; }
    void set_next(Tree<_Tp, _Al> next) { next_ = &next; }
    void set_next(Tree<_Tp, _Al>* next) { next_ = next; }
    void set_prev(Tree<_Tp, _Al> prev) { prev_ = &prev; }
    void set_prev(Tree<_Tp, _Al>* prev) { prev_ = prev; }

    child_reference at(size_type pos) { return children_.at(pos); }
    const_child_reference at(size_type pos) const { return children_.at(pos); }

    child_reference operator[](size_type pos) { return children_[pos]; }
    const_child_reference operator[](size_type pos) const { return children_[pos]; }

    reference front() {return children_.front();}
    const_reference front() const {return children_.front();}

    reference back() {return children_.back();}
    const_reference back() const {return children_.back();}

    iterator begin() noexcept { return iterator(&children_.front()); }
    const_iterator begin() const noexcept { return const_iterator(&children_.front()); }
    const_iterator cbegin() const noexcept { return const_iterator(&children_.front()); }

    iterator end() noexcept { return ++iterator(&children_.back()); }
    const_iterator end() const noexcept { return ++const_iterator(&children_.back()); }
    const_iterator cend() const noexcept { return ++const_iterator(&children_.back()); }

    // iterator rbegin() noexcept { return iterator(&children_.front()); }
    // const_iterator rbegin() const noexcept { return const_iterator(&children_.front()); }
    // const_iterator rcbegin() const noexcept { return const_iterator(&children_.front()); }
    //
    // iterator rend() noexcept { return iterator(++(&children_.back())); }
    // const_iterator rend() const noexcept { return const_iterator(++(&children_.back())); }
    // const_iterator rcend() const noexcept { return const_iterator(++(&children_.back())); }

    child_reference child_front() { return children_.front(); }
    const_child_reference child_front() const { return children_.front(); }

    child_reference child_back() { return children_.back(); }
    const_child_reference child_back() const { return children_.back(); }

    child_iterator child_begin() noexcept { return children_.begin(); }
    const_child_iterator child_begin() const noexcept { return children_.begin(); }
    const_child_iterator cchild_begin() const noexcept { return children_.cbegin(); }

    child_iterator child_end() noexcept { return children_.end(); }
    const_child_iterator child_end() const noexcept { return children_.end(); }
    const_child_iterator cchild_end() const noexcept { return children_.cend(); }

    child_iterator rchild_begin() noexcept { return children_.rbegin(); }
    const_child_iterator rchild_begin() const noexcept { return children_.rbegin(); }
    const_child_iterator crchild_begin() const noexcept { return children_.crbegin(); }

    child_iterator rchild_end() noexcept { return children_.rend(); }
    const_child_iterator rchild_end() const noexcept { return children_.rend(); }
    const_child_iterator crchild_end() const noexcept { return children_.crend(); }

    bool empty() const noexcept { return children_.empty(); }
    size_type size() const noexcept { return children_.size(); }
    size_type max_size() const noexcept { return children_.max_size(); }

    void clear() noexcept { children_.clear(); }

    child_iterator insert(child_iterator pos, const _Tp& value) {
      Tree<_Tp, _Al>*prev = nullptr, *next = nullptr;
      if (pos != children_.begin()) {
        prev = &*(--pos);
      }
      if (pos != children_.end() - 1) {
        next = &*(++pos);
      }
      child_iterator it =
          children_.insert(pos, Tree<_Tp, _Al>(value, this, prev, next));
      if (prev != nullptr) {
        prev->next_ = &*it;
      }
      if (next != nullptr) {
        next->prev_ = &*it;
      }
      return it;
    }
    child_iterator insert(child_iterator pos, _Tp&& value) {
      Tree<_Tp, _Al>*prev = nullptr, *next = nullptr;
      if (pos != children_.begin()) {
        prev = &*(--pos);
      }
      if (pos != children_.end() - 1) {
        next = &*(++pos);
      }
      child_iterator it =
          children_.insert(pos, Tree<_Tp, _Al>(value, this, prev, next));
      if (prev != nullptr) {
        prev->next_ = &*it;
      }
      if (next != nullptr) {
        next->prev_ = &*it;
      }
      return it;
    }

    child_iterator erase(const_child_iterator pos) {
      child_iterator it = children_.erase(pos);
      if (pos != children_.begin()) {
        (--it)->next_ = *it;
      }
      if (it != children_.end()) {
        it->prev_ = *(--it);
      }
      return it;
    }
    child_iterator erase(const_child_iterator first, const_child_iterator last) {
      return children_.erase(first, last);
    }

    void push_child_back(const _Tp& value) {
      Tree<_Tp, _Al>* prev = nullptr;
      if (children_.size() != 0) {
        prev = &children_.back();
      }
      children_.push_child_back(Tree<_Tp, _Al>(value, this, prev, nullptr));
      if (prev != nullptr) {
        prev->next_ = &children_.back();
      }
    }
    void push_child_back(_Tp&& value) {
      Tree<_Tp, _Al>* prev = nullptr;
      if (children_.size() != 0) {
        prev = &children_.back();
      }
      children_.push_child_back(Tree<_Tp, _Al>(value, this, prev, nullptr));
      if (prev != nullptr) {
        prev->next_ = &children_.back();
      }
    }

    void pop_child_back() {
      children_.pop_back();
      if (children_.size() != 0) {
        children_.back().next_ = nullptr;
      }
    }

    void append(const _Tp& value) {
      Tree<_Tp, _Al>* prev = nullptr;
      if (children_.size() != 0) {
        prev = &children_.end();
      }
      children_.push_back(Tree<_Tp, _Al>(value, this, prev, nullptr));
      if (prev != nullptr) {
        prev->next_ = &children_.back();
      }
    }
    void append(_Tp&& value) {
      Tree<_Tp, _Al>* prev = nullptr;
      if (children_.size() != 0) {
        prev = &*(--children_.end());
      }
      children_.push_back(Tree<_Tp, _Al>(value, this, prev, nullptr));
      if (prev != nullptr) {
        prev = &*(children_.end() - 2);
        prev->next_ = &*(--children_.end());
      }
    }
    void prepend(const _Tp& value) {
      Tree<_Tp, _Al>* next = nullptr;
      if (children_.size() != 0) {
        next = &children_.front();
      }
      children_.insert(children_.begin(),
                       Tree<_Tp, _Al>(value, this, nullptr, next));
      if (next != nullptr) {
        next->prev_ = &children_.front();
      }
    }
    void prepend(_Tp&& value) {
      Tree<_Tp, _Al>* next = nullptr;
      if (children_.size() != 0) {
        next = &children_.front();
      }
      children_.insert(children_.begin(),
                       Tree<_Tp, _Al>(value, this, nullptr, next));
      if (next != nullptr) {
        next->prev_ = &children_.front();
      }
    }

    _Tp node;

   private:
    Tree<_Tp, _Al>*parent_, *next_, *prev_;
    std::vector<Tree<_Tp, _Al>> children_;
  };

  template <typename _Tp>
  std::string pretty(Tree<_Tp> tree, std::size_t indent = 2) {
    std::stringstream ss;
    ss << tree.node;
    std::string ret = ss.str();
    std::string repr = "\u2502" + std::string(indent, ' ');
    std::string bar;
    for (std::size_t i = 0; i < indent; i++) {
      bar += "\u2500";
    }
    if (tree.size() != 0) {
      ret += "\n";
    }
    for (typename Tree<_Tp>::child_iterator it = tree.child_begin(); it != tree.child_end();
         ++it) {
      if (it != tree.child_end() - 1) {
        ret += "\u251c" + bar;
      } else {
        ret += "\u2514" + bar;
        repr = std::string(indent + 1, ' ');
      }
      std::string sub = pretty(*it, indent);
      std::size_t pos = 0;
      while ((pos = sub.find('\n', pos)) != std::string::npos) {
        sub.insert(++pos, repr);
        pos += repr.length();
      }
      ret += sub;
      if (it != (--tree.child_end())) {
        ret += '\n';
      }
    }
    return ret;
  }

  template <typename _Tp>
  std::ostream& operator<<(std::ostream& out, Tree<_Tp> tree) {
    out << tree.node;
    if (tree.size() != 0) {
      out << '[';
      for (typename Tree<_Tp>::child_iterator it = tree.child_begin(); it != tree.child_end();
           ++it) {
        out << (*it);
        if (it != (--tree.child_end())) {
          out << ',';
        }
      }
      out << ']';
    }
    return out;
  }
}  // namespace tree
}  // namespace estl

#endif  // ESTL_TREE_HPP_
