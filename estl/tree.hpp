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
  class Node_ {
   public:
    Node_()
        : node(_Tp()),
          parent_(nullptr),
          first_(nullptr),
          last_(nullptr),
          prev_(nullptr),
          next_(nullptr) {}
    Node_(const _Tp& value)
        : node(value),
          parent_(nullptr),
          first_(nullptr),
          last_(nullptr),
          prev_(nullptr),
          next_(nullptr) {}
    Node_(_Tp&& value)
        : node(value),
          parent_(nullptr),
          first_(nullptr),
          last_(nullptr),
          prev_(nullptr),
          next_(nullptr) {}
    _Tp node;
    Node_ *parent_, *first_, *last_, *prev_, *next_;

   private:
  };
  template <typename _Tp, typename _Al = std::allocator<_Tp>>
  class Tree {
   public:
    class depth_iterator {
     public:
      depth_iterator() : node_(nullptr) {}
      depth_iterator(Node_<_Tp, _Al>* node) : node_(node) {}

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
          throw std::logic_error(
              "Tree(depth_iterator) iterator node is uninitialized");
        }
        if (node_->first_ != nullptr) {
          node_ = node_->first_;
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
        if (node_ == nullptr) {
          throw std::logic_error("Tree iterator node in uninitialized");
        }
        if (node_->prev_ != nullptr) {
          node_ = node_->prev_;
          while (node_->last_ != nullptr) {
            node_ = node_->last_;
          }
        } else {
          node_ = node_->parent_;
        }
        return *this;
      }
      depth_iterator& operator+=(unsigned n) {
        while (n > 0) {
          ++(*this);
          --n;
        }
        return *this;
      }
      depth_iterator& operator-=(unsigned n) {
        while (n > 0) {
          --(*this);
          --n;
        }
        return *this;
      }
      Node_<_Tp, _Al>* node_;
    };

    typedef _Al allocator_type;
    typedef typename _Al::value_type value_type;
    typedef Tree<_Tp, _Al>& reference;
    typedef const Tree<_Tp, _Al>& const_reference;
    typedef typename _Al::difference_type difference_type;
    typedef typename _Al::size_type size_type;
    typedef typename _Al::pointer pointer;
    typedef typename _Al::const_pointer const_pointer;
    typedef depth_iterator iterator;
    typedef const depth_iterator const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    Tree() { initialize(); }
    Tree(const _Tp& val) {
      initialize();
      head->node = val;
    }
    Tree(_Tp&& val) {
      initialize();
      head->node = val;
    }
    Tree(const Node_<_Tp, _Al>& val){
      initialize();
      head->node = val.node;
      head->first_ = val.first_;
      head->last_= val.last_;
    }
    // Tree(const Tree<_Tp, _Al>& copy)
    //     : node(copy.node), children_(copy.children_) {}
    ~Tree() {}

    Tree<_Tp, _Al>& operator=(const _Tp& val) {
      head->node = val;
      return *this;
    }
    Tree<_Tp, _Al>& operator=(const Tree<_Tp, _Al>& copy) {
      head->node = copy.node;
      // children_ = copy.children_;
      return *this;
    }

    // reference at(size_type pos) { return children_.at(pos); }
    // const_reference at(size_type pos) const { return children_.at(pos); }
    //
    // reference operator[](size_type pos) { return children_[pos]; }
    // const_reference operator[](size_type pos) const { return children_[pos];
    // }

    reference front() { return *head->first_; }
    const_reference front() const { return *head->first_; }

    reference back() { return *head->last_; }
    const_reference back() const { return *head->last_; }

    iterator begin() noexcept { return iterator(head); }
    const_iterator begin() const noexcept { return const_iterator(head); }
    const_iterator cbegin() const noexcept { return const_iterator(head); }

    iterator end() noexcept { return iterator(foot); }
    const_iterator end() const noexcept { return const_iterator(foot); }
    const_iterator cend() const noexcept { return const_iterator(foot); }

    reverse_iterator rbegin() noexcept { return reverse_iterator(head); }
    const_reverse_iterator rbegin() const noexcept {
      return const_reverse_iterator(head);
    }
    const_reverse_iterator crbegin() const noexcept {
      return const_reverse_iterator(head);
    }

    reverse_iterator rend() noexcept { return reverse_iterator(foot); }
    const_reverse_iterator rend() const noexcept {
      return const_reverse_iterator(foot);
    }
    const_reverse_iterator crend() const noexcept {
      return const_reverse_iterator(foot);
    }

    bool empty() const noexcept { return (begin() == end()); }
    size_type size() const noexcept {
      size_type count = 0;
      for (depth_iterator it = begin(); it != end(); ++it) {
        ++count;
      }
      return count;
    }

    void clear() noexcept {
      while (head->next_ != foot) {
        erase(iterator(head->next_));
      }
    }

    iterator insert(const_iterator pos, const _Tp& value) {
      if (pos.node_ == nullptr) {
        pos.node_ = foot;
      }
      if (pos.node_ == this) {
        throw std::logic_error("Tree(insert) pos must be initialized");
      }
      Node_<_Tp, _Al>* nd = alloc_.allocate(1, 0);
      alloc_.construct(nd);
      nd->node = value;
      nd->parent_ = pos->parent_;
      nd->next_ = pos;
      nd->prev_ = pos->prev_;
      pos->prev_ = nd;
      if (nd->prev_ == nullptr) {
        if (nd->parent_ != nullptr) {
          nd->parent_->first_ = nd;
        }
      } else {
        nd->prev_->next_ = nd;
      }
      return iterator(nd);
    }

    iterator insert(const_iterator pos, _Tp&& value) {
      if (pos.node_ == nullptr) {
        pos.node_ = foot;
      }
      if (pos.node_ == this) {
        throw std::logic_error("Tree(insert) pos must be initialized");
      }
      Node_<_Tp, _Al>* nd = alloc_.allocate(1, 0);
      alloc_.construct(nd);
      nd->node = value;
      nd->parent_ = pos->parent_;
      nd->next_ = pos;
      nd->prev_ = pos->prev_;
      pos->prev_ = nd;
      if (nd->prev_ == nullptr) {
        if (nd->parent_ != nullptr) {
          nd->parent_->first_ = nd;
        }
      } else {
        nd->prev_->next_ = nd;
      }
      return iterator(nd);
    }

    iterator erase(const_iterator pos) {
      erase_children(pos);
      if (pos->prev_ == nullptr) {
        pos->parent_->first_ = pos->next_;
      } else {
        pos->next_->prev_ = pos->prev_;
      }
      if (pos->next_ == nullptr) {
        pos->parent_->last_ = pos->prev_;
      } else {
        pos->next_->prev_ = pos->prev_;
      }
      alloc_.destroy(pos.node_);
      alloc_.deallocate(pos.node_, 1);
    }

    void erase_children(const iterator& pos) {
      if (pos.node_ == nullptr) {
        return;
      }
      Tree<_Tp, _Al>*current = pos->first_, *prev = nullptr;
      while (current != nullptr) {
        prev = current;
        current = current->next_;

        erase_children(iterator(prev));
        alloc_.destroy(prev);
        alloc_.deallocate(prev, 1);
      }
      pos->first_ = nullptr;
      pos->last_ = nullptr;
    }

    // void push_back(const _Tp& value) {
    //   Tree<_Tp, _Al>* prev = nullptr;
    //   if (children_.size() != 0) {
    //     prev = &children_.back();
    //   }
    //   children_.push_back(Tree<_Tp, _Al>(value, this, prev, nullptr));
    //   if (prev != nullptr) {
    //     prev->next_ = &children_.back();
    //   }
    // }
    // void push_back(_Tp&& value) {
    //   Tree<_Tp, _Al>* prev = nullptr;
    //   if (children_.size() != 0) {
    //     prev = &children_.back();
    //   }
    //   children_.push_back(Tree<_Tp, _Al>(value, this, prev, nullptr));
    //   if (prev != nullptr) {
    //     prev->next_ = &children_.back();
    //   }
    // }
    //
    // void pop_back() {
    //   children_.pop_back();
    //   if (children_.size() != 0) {
    //     children_.back().next_ = nullptr;
    //   }
    // }

    void append(const _Tp& value) {
      Node_<_Tp, _Al>* nd = alloc_.allocate(1, 0);
      alloc_.construct(nd);
      nd->node = value;
      nd->parent_ = head;
      if (head->last_ != nullptr) {
        nd->prev_ = head->last_;
        nd->prev_->next_ = nd;
      } else {
        head->first_ = nd;
      }
      head->last_ = nd;
    }
    // void append(_Tp&& value) {
    //   Tree<_Tp, _Al>* prev = nullptr;
    //   if (children_.size() != 0) {
    //     prev = &*(--children_.end());
    //   }
    //   children_.push_back(Tree<_Tp, _Al>(value, this, prev, nullptr));
    //   if (prev != nullptr) {
    //     prev = &*(children_.end() - 2);
    //     prev->next_ = &*(--children_.end());
    //   }
    // }
    void prepend(const _Tp& value) {
      Node_<_Tp, _Al>* nd = alloc_.allocate(1, 0);
      alloc_.construct(nd);
      nd->node = value;
      nd->parent_ = head;
      if (head->first_ != nullptr) {
        nd->next_ = head->first_;
        head->first_->prev_ = nd;
      } else {
        head->last_ = nd;
      }
      head->first_ = nd;
    }
    // void prepend(_Tp&& value) {
    //   Tree<_Tp, _Al>* next = nullptr;
    //   if (children_.size() != 0) {
    //     next = &children_.front();
    //   }
    //   children_.insert(children_.begin(),
    //                    Tree<_Tp, _Al>(value, this, nullptr, next));
    //   if (next != nullptr) {
    //     next->prev_ = &children_.front();
    //   }
    // }
    
    Tree<_Tp, _Al> subtree(const_iterator pos){
      Tree<_Tp, _Al> tmp;
      tmp.head = pos.node_;
      tmp.head->node = pos.node_->node;
      // tmp.head->first_ = pos.node_->first_;
      // tmp.head->last_= pos.node_->last_;
      // tmp.head->next_ = tmp.foot;
      std::cout << tmp.head->next_ << "\n";
      std::cout << tmp.foot << "\n";
      tmp.head->next_ = tmp.foot;
      tmp.foot->prev_ = tmp.head;
      return tmp;
    }
    
    Node_<_Tp, _Al>*head, *foot;
    private:
    void initialize() {
      head = alloc_.allocate(1, nullptr);
      foot = alloc_.allocate(1, nullptr);
      alloc_.construct(head, Node_<_Tp, _Al>());
      alloc_.construct(foot, Node_<_Tp, _Al>());

      head->next_ = foot;

      foot->prev_ = head;
    }


    std::allocator<Node_<_Tp, _Al>> alloc_;
  };

  template <typename _Tp>
  std::string pretty(Tree<_Tp> tree, std::size_t indent = 2) {
    return pretty(tree.head, indent);
  }
  template <typename _Tp>
  std::string pretty(Node_<_Tp>* tree, std::size_t indent = 2) {
    std::stringstream ss;
    ss << tree->node;
    std::string ret = ss.str();
    std::string repr = "\u2502" + std::string(indent, ' ');
    std::string bar;
    for (std::size_t i = 0; i < indent; i++) {
      bar += "\u2500";
    }
    if (tree->first_ != nullptr) {
      ret += "\n";
      Node_<_Tp>* it = tree->first_;
      while (it != tree->last_) {
        ret += "\u251c" + bar;
        std::string sub = pretty(it, indent);
        std::size_t pos = 0;
        while ((pos = sub.find('\n', pos)) != std::string::npos) {
          sub.insert(++pos, repr);
          pos += repr.length();
        }
        ret += sub + '\n';
        it = it->next_;
      }
      ret += "\u2514" + bar;
      repr = std::string(indent + 1, ' ');
      std::string sub = pretty(it, indent);
      std::size_t pos = 0;
      while ((pos = sub.find('\n', pos)) != std::string::npos) {
        sub.insert(++pos, repr);
        pos += repr.length();
      }
      ret += sub;
    }
    return ret;
  }

  template <typename _Tp>
  std::ostream& operator<<(std::ostream& out, Tree<_Tp> tree) {
    out << tree.node;
    if (tree.size() != 0) {
      out << '[';
      for (typename Tree<_Tp>::iterator it = tree.begin(); it != tree.end();
           ++it) {
        out << (*it);
        if (it != (--tree.end())) {
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
