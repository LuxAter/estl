#ifndef ESTL_TREE_HPP_
#define ESTL_TREE_HPP_

#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace estl {
namespace tree {
  template <typename _Tp, typename _Al = std::allocator<_Tp>>
  class Tree {
   public:
    class iterator_base {
     public:
      typedef _Al allocator_type;
      typedef typename _Al::value_type value_type;
      typedef typename _Al::reference reference;
      typedef typename _Al::const_reference const_reference;
      typedef typename _Al::difference_type difference_type;
      typedef typename _Al::size_type size_type;
      typedef typename _Al::pointer pointer;
      typedef typename _Al::const_pointer const_pointer;
      typedef std::random_access_iterator_tag iterator_category;
    };
    class depth_iterator : public iterator_base {
     public:
      depth_iterator() : node_(nullptr) {}
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
          throw std::logic_error(
              "Tree(depth_iterator) iterator node is uninitialized");
        }
        if (node_->first_ != nullptr) {
          node_ = node_->first_;
        } else {
          while (node_->parent_ != nullptr &&
                 node_->parent_->parent_ != nullptr &&
                 node_->next_ == node_->parent_->foot_) {
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
      depth_iterator& operator++(int) {
        depth_iterator copy = *this;
        ++(*this);
        return copy;
      }
      depth_iterator& operator--(int) {
        depth_iterator copy = *this;
        --(*this);
        return copy;
      }
      depth_iterator& operator+(unsigned n) {
        while (n > 0) {
          ++(*this);
          --n;
        }
        return *this;
      }
      depth_iterator& operator-(unsigned n) {
        while (n > 0) {
          ++(*this);
          --n;
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
      Tree<_Tp, _Al>* node_;
    };
    class sibling_iterator : public iterator_base {
     public:
      sibling_iterator() : node_(nullptr) {}
      sibling_iterator(Tree<_Tp, _Al>* node) : node_(node) {}

      _Tp& operator*() const { return node_->node; }
      _Tp* operator->() const { return &(node_->node); }

      bool operator==(const sibling_iterator& rhs) const {
        if (rhs.node_ == node_) {
          return true;
        } else {
          return false;
        }
      }
      bool operator!=(const sibling_iterator& rhs) const {
        if (rhs.node_ != node_) {
          return true;
        } else {
          return false;
        }
      }
      sibling_iterator& operator++() {
        if (node_ == nullptr) {
          throw std::logic_error(
              "Tree(depth_iterator) iterator node is uninitialized");
        }
        node_ = node_->next_;
        return *this;
      }
      sibling_iterator& operator--() {
        if (node_ == nullptr) {
          throw std::logic_error(
              "Tree(depth_iterator) iterator node is uninitialized");
        }
        node_ = node_->prev_;
        return *this;
      }
      sibling_iterator& operator+(unsigned n) {
        while (n > 0) {
          ++(*this);
          --n;
        }
        return *this;
      }
      sibling_iterator& operator-(unsigned n) {
        while (n > 0) {
          --(*this);
          --n;
        }
        return *this;
      }
      sibling_iterator& operator+=(unsigned n) {
        while (n > 0) {
          ++(*this);
          --n;
        }
        return *this;
      }
      sibling_iterator& operator-=(unsigned n) {
        while (n > 0) {
          --(*this);
          --n;
        }
        return *this;
      }
      Tree<_Tp, _Al>* node_;
    };
    class leaf_iterator : public iterator_base {
     public:
      leaf_iterator() : node_(nullptr) {}
      leaf_iterator(Tree<_Tp, _Al>* node) : node_(node) {}

      _Tp& operator*() const { return node_->node; }
      _Tp* operator->() const { return &(node_->node); }

      bool operator==(const leaf_iterator& rhs) const {
        if (rhs.node_ == node_) {
          return true;
        } else {
          return false;
        }
      }
      bool operator!=(const leaf_iterator& rhs) const {
        if (rhs.node_ != node_) {
          return true;
        } else {
          return false;
        }
      }
      leaf_iterator& operator++() {
        if (node_ == nullptr) {
          throw std::logic_error(
              "Tree(depth_iterator) iterator node is uninitialized");
        }
        if (node_->first_ != nullptr) {
          while (node_->first_ != nullptr) {
            node_ = node_->first_;
          }
        } else {
          while (node_->parent_ != nullptr &&
                 node_->parent_->parent_ != nullptr &&
                 node_->next_ == node_->parent_->foot_) {
            node_ = node_->parent_;
          }
          node_ = node_->next_;
          while (node_->first_ != nullptr) {
            node_ = node_->first_;
          }
          return *this;
        }

        if (node_->first_ != nullptr) {
          node_ = node_->first_;
        } else {
          while (node_->parent_ != nullptr &&
                 node_->parent_->parent_ != nullptr &&
                 node_->next_ == node_->parent_->foot_) {
            node_ = node_->parent_;
          }
          node_ = node_->next_;
        }
        return *this;
      }
      leaf_iterator& operator--() {
        if (node_ == nullptr) {
          throw std::logic_error(
              "Tree(depth_iterator) iterator node is uninitialized");
        }
        node_ = node_->prev_;
        return *this;
      }
      leaf_iterator& operator+(unsigned n) {
        while (n > 0) {
          ++(*this);
          --n;
        }
        return *this;
      }
      leaf_iterator& operator-(unsigned n) {
        while (n > 0) {
          --(*this);
          --n;
        }
        return *this;
      }
      leaf_iterator& operator+=(unsigned n) {
        while (n > 0) {
          ++(*this);
          --n;
        }
        return *this;
      }
      leaf_iterator& operator-=(unsigned n) {
        while (n > 0) {
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
    typedef typename _Al::difference_type difference_type;
    typedef typename _Al::size_type size_type;
    typedef typename _Al::pointer pointer;
    typedef typename _Al::const_pointer const_pointer;
    typedef depth_iterator iterator;
    typedef const depth_iterator const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef sibling_iterator sibling_iterator;
    typedef const sibling_iterator const_sibling_iterator;
    typedef std::reverse_iterator<sibling_iterator> reverse_sibling_iterator;
    typedef std::reverse_iterator<const_sibling_iterator>
        const_reverse_sibling_iterator;
    typedef leaf_iterator leaf_iterator;
    typedef const leaf_iterator const_leaf_iterator;
    typedef std::reverse_iterator<leaf_iterator> reverse_leaf_iterator;
    typedef std::reverse_iterator<const_leaf_iterator>
        const_reverse_leaf_iterator;

    Tree()
        : node(_Tp()),
          parent_(nullptr),
          prev_(nullptr),
          next_(nullptr),
          first_(nullptr),
          last_(nullptr),
          foot_(nullptr) {}
    Tree(const _Tp& val)
        : node(val),
          parent_(nullptr),
          prev_(nullptr),
          next_(nullptr),
          first_(nullptr),
          last_(nullptr),
          foot_(nullptr) {}
    Tree(_Tp&& val)
        : node(val),
          parent_(nullptr),
          prev_(nullptr),
          next_(nullptr),
          first_(nullptr),
          last_(nullptr),
          foot_(nullptr) {}
    // Tree(const Tree<_Tp, _Al>& copy)
    //     : node(copy.node), children_(copy.children_) {}
    ~Tree() {}

    Tree<_Tp, _Al>& operator=(const _Tp& val) {
      this->node = val;
      return *this;
    }
    Tree<_Tp, _Al>& operator=(const Tree<_Tp, _Al>& copy) {
      this->node = copy.node;
      // children_ = copy.children_;
      return *this;
    }

    // reference at(size_type pos) { return children_.at(pos); }
    // const_reference at(size_type pos) const { return children_.at(pos); }
    //
    // reference operator[](size_type pos) { return children_[pos]; }
    // const_reference operator[](size_type pos) const { return children_[pos];
    // }

    reference front() { return *this->first_; }
    const_reference front() const { return *this->first_; }

    reference back() { return *this->last_; }
    const_reference back() const { return *this->last_; }

    iterator begin() noexcept { return iterator(this); }
    const_iterator begin() const noexcept { return const_iterator(this); }
    const_iterator cbegin() const noexcept { return const_iterator(this); }

    iterator end() noexcept { return iterator(foot_); }
    const_iterator end() const noexcept { return const_iterator(foot_); }
    const_iterator cend() const noexcept { return const_iterator(foot_); }

    reverse_iterator rbegin() noexcept { return reverse_iterator(this); }
    const_reverse_iterator rbegin() const noexcept {
      return const_reverse_iterator(this);
    }
    const_reverse_iterator crbegin() const noexcept {
      return const_reverse_iterator(this);
    }

    reverse_iterator rend() noexcept { return reverse_iterator(foot_); }
    const_reverse_iterator rend() const noexcept {
      return const_reverse_iterator(foot_);
    }
    const_reverse_iterator crend() const noexcept {
      return const_reverse_iterator(foot_);
    }

    sibling_iterator child_begin() noexcept { return sibling_iterator(first_); }
    const_sibling_iterator child_begin() const noexcept {
      return const_sibling_iterator(first_);
    }
    const_sibling_iterator cchild_begin() const noexcept {
      return const_sibling_iterator(first_);
    }

    sibling_iterator child_end() noexcept { return sibling_iterator(foot_); }
    const_sibling_iterator child_end() const noexcept {
      return const_sibling_iterator(foot_);
    }
    const_sibling_iterator cchild_end() const noexcept {
      return const_sibling_iterator(foot_);
    }

    reverse_sibling_iterator rchild_begin() noexcept {
      return reverse_sibling_iterator(first_);
    }
    const_reverse_sibling_iterator rchild_begin() const noexcept {
      return const_reverse_sibling_iterator(first_);
    }
    const_reverse_sibling_iterator crchild_begin() const noexcept {
      return const_reverse_sibling_iterator(first_);
    }

    reverse_sibling_iterator rchild_end() noexcept {
      return reverse_sibling_iterator(foot_);
    }
    const_reverse_sibling_iterator rchild_end() const noexcept {
      return const_reverse_sibling_iterator(foot_);
    }
    const_reverse_sibling_iterator crchild_end() const noexcept {
      return const_reverse_sibling_iterator(foot_);
    }

    leaf_iterator leaf_begin() noexcept { return leaf_iterator(first_); }
    const_leaf_iterator leaf_begin() const noexcept {
      return const_leaf_iterator(first_);
    }
    const_leaf_iterator cleaf_begin() const noexcept {
      return const_leaf_iterator(first_);
    }

    leaf_iterator leaf_end() noexcept { return leaf_iterator(foot_); }
    const_leaf_iterator leaf_end() const noexcept {
      return const_leaf_iterator(foot_);
    }
    const_leaf_iterator cleaf_end() const noexcept {
      return const_leaf_iterator(foot_);
    }

    reverse_leaf_iterator rleaf_begin() noexcept {
      return reverse_leaf_iterator(first_);
    }
    const_reverse_leaf_iterator rleaf_begin() const noexcept {
      return const_reverse_leaf_iterator(first_);
    }
    const_reverse_leaf_iterator crleaf_begin() const noexcept {
      return const_reverse_leaf_iterator(first_);
    }

    reverse_leaf_iterator rleaf_end() noexcept {
      return reverse_leaf_iterator(foot_);
    }
    const_reverse_leaf_iterator rleaf_end() const noexcept {
      return const_reverse_leaf_iterator(foot_);
    }
    const_reverse_leaf_iterator crleaf_end() const noexcept {
      return const_reverse_leaf_iterator(foot_);
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
      while (this->next_ != foot_) {
        erase(iterator(this->next_));
      }
    }

    iterator insert(const_iterator pos, const _Tp& value) {
      if (pos.node_ == nullptr) {
        pos.node_ = foot_;
      }
      if (pos.node_ == this) {
        throw std::logic_error("Tree(insert) pos must be initialized");
      }
      Tree<_Tp, _Al>* nd = alloc_.allocate(1, 0);
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

    template <typename _Iter>
    typename std::enable_if<std::is_base_of<iterator_base, _Iter>::value,
                            _Iter>::type
    insert(_Iter pos, _Tp&& value) {
      Tree<_Tp, _Al>* nd = alloc_.allocate(1, 0);
      alloc_.construct(nd, value);
      nd->parent_ = pos.node_->parent_;
      nd->next_ = pos.node_;
      nd->prev_ = pos.node_->prev_;
      pos.node_->prev_ = nd;
      if (nd->prev_ == nullptr) {
        if (nd->parent_ != nullptr) {
          nd->parent_->first_ = nd;
        }
      } else {
        nd->prev_->next_ = nd;
      }
      return _Iter(nd);
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

    void push_back(const _Tp& value) { append(value); }
    void push_back(_Tp&& value) { append(value); }

    void pop_back() {
      if (last_ != nullptr) {
        Tree<_Tp, _Al>* nd = last_->prev_;
        nd->next_ = foot_;
        alloc_.destroy(last_);
        alloc_.deallocate(last_, 1);
        last_ = nd;
      }
    }

    void append(const _Tp& value) {
      Tree<_Tp, _Al>* nd = alloc_.allocate(1, nullptr);
      alloc_.construct(nd);
      nd->node = value;
      nd->parent_ = this;
      if (foot_ == nullptr) {
        initialize();
      }
      nd->next_ = foot_;
      foot_->prev_ = nd;
      if (this->last_ != nullptr) {
        nd->prev_ = this->last_;
        nd->prev_->next_ = nd;
      } else {
        this->first_ = nd;
      }
      this->last_ = nd;
    }
    void append(_Tp&& value) {
      Tree<_Tp, _Al>* nd = alloc_.allocate(1, nullptr);
      alloc_.construct(nd);
      nd->node = value;
      nd->parent_ = this;
      if (foot_ == nullptr) {
        initialize();
      }
      nd->next_ = foot_;
      foot_->prev_ = nd;
      if (this->last_ != nullptr) {
        nd->prev_ = this->last_;
        nd->prev_->next_ = nd;
      } else {
        this->first_ = nd;
      }
      this->last_ = nd;
    }
    void prepend(const _Tp& value) {
      Tree<_Tp, _Al>* nd = alloc_.allocate(1, nullptr);
      alloc_.construct(nd);
      nd->node = value;
      nd->parent_ = this;
      if (foot_ == nullptr) {
        initialize();
      }
      if (this->first_ != nullptr) {
        nd->next_ = this->first_;
        this->first_->prev_ = nd;
      } else {
        this->last_ = nd;
        nd->next_ = foot_;
        foot_->prev_ = nd;
      }
      this->first_ = nd;
    }
    void prepend(_Tp&& value) {
      Tree<_Tp, _Al>* nd = alloc_.allocate(1, nullptr);
      alloc_.construct(nd);
      nd->node = value;
      nd->parent_ = this;
      if (foot_ == nullptr) {
        initialize();
      }
      if (this->first_ != nullptr) {
        nd->next_ = this->first_;
        this->first_->prev_ = nd;
      } else {
        this->last_ = nd;
        nd->next_ = foot_;
        foot_->prev_ = nd;
      }
      this->first_ = nd;
    }

    _Tp node;
    Tree<_Tp, _Al>*parent_, *prev_, *next_, *first_, *last_, *foot_;

   private:
    void initialize() {
      foot_ = alloc_.allocate(1, nullptr);
      alloc_.construct(foot_, Tree<_Tp, _Al>());
      foot_->parent_ = this;
    }

    std::allocator<Tree<_Tp, _Al>> alloc_;
  };

  template <typename _Tp>
  std::string pretty(Tree<_Tp> tree, std::size_t indent = 2) {
    return pretty(&tree, indent);
  }
  template <typename _Tp>
  std::string pretty(Tree<_Tp>* tree, std::size_t indent = 2) {
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
      Tree<_Tp>* it = tree->first_;
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
  std::ostream& operator<<(std::ostream& out, Tree<_Tp>& tree) {
    out << tree.node;
    if (tree.first_ != nullptr) {
      out << '[';
      for (typename Tree<_Tp>::sibling_iterator it = tree.child_begin();
           it != tree.child_end(); ++it) {
        out << *it.node_;
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
