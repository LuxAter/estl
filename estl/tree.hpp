#ifndef ESTL_TREE_HPP_
#define ESTL_TREE_HPP_

#include <algorithm>
#include <cassert>
#include <iterator>
#include <queue>
#include <set>
#include <sstream>

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <memory>
#include <queue>
#include <set>
#include <stdexcept>

namespace estl {
namespace tree {
  template <typename _Tp>
  class TreeNode_ {
   public:
    TreeNode_()
        : parent(0),
          first_child(0),
          last_child(0),
          prev_sibling(0),
          next_sibling(0) {}
    TreeNode_(const _Tp& val)
        : parent(0),
          first_child(0),
          last_child(0),
          prev_sibling(0),
          next_sibling(0),
          data(val) {}
    TreeNode_(_Tp&& val)
        : parent(0),
          first_child(0),
          last_child(0),
          prev_sibling(0),
          next_sibling(0),
          data(val) {}
    TreeNode_<_Tp>* parent;
    TreeNode_<_Tp>*first_child, *last_child;
    TreeNode_<_Tp>*prev_sibling, *next_sibling;
    _Tp data;
  };
  template <typename _Tp, typename _Al = std::allocator<TreeNode_<_Tp>>,
            typename _AlTp = std::allocator<_Tp>>
  class Tree {
   protected:
    typedef TreeNode_<_Tp> Node_;

   public:
    typedef _Tp value_type;

    class iterator_base;
    class sibling_iterator;
    class leaf_iterator;
    class pre_order_iterator;
    class post_order_iterator;

    typedef pre_order_iterator iterator;

    class iterator_base {
     public:
      typedef _AlTp allocator_type;
      typedef typename _AlTp::value_type value_type;
      typedef typename _AlTp::reference reference;
      typedef typename _AlTp::const_reference const_reference;
      typedef typename _AlTp::difference_type difference_type;
      typedef typename _AlTp::size_type size_type;
      typedef typename _AlTp::pointer pointer;
      typedef typename _AlTp::const_pointer const_pointer;
      typedef typename _AlTp::pointer iterator;
      typedef typename _AlTp::const_pointer const_iterator;
      typedef std::bidirectional_iterator_tag iterator_category;

      iterator_base() : node(0), skip_children_(false) {}
      iterator_base(Node_* tn) : node(tn), skip_children_(false) {}
      reference operator*() const { return node->data; }
      pointer operator->() const { return &(node->data); }

      void skip_children() { skip_children_ = true; }
      void skip_children(bool skip) { skip_children_ = skip; }
      std::size_t number_of_children() const {
        Node_* pos = node->first_child;
        if (pos == nullptr) {
          return 0;
        }
        std::size_t ret = 1;
        while (pos != node->last_child) {
          ++ret;
          pos = pos->next_sibling;
        }
        return ret;
      }

      sibling_iterator begin() const {
        if (node->first_child == nullptr) {
          return end();
        } else {
          sibling_iterator ret(node->first_child);
          ret.parent_ = this->node;
          return ret;
        }
      }
      sibling_iterator end() const {
        sibling_iterator ret(nullptr);
        ret.parent_ = node;
        return ret;
      }

      Node_* node;

     protected:
      bool skip_children_;
    };
    class pre_order_iterator : public iterator_base {
     public:
      pre_order_iterator() : iterator_base(nullptr) {}
      pre_order_iterator(Node_* tn) : iterator_base(tn) {}
      pre_order_iterator(const iterator_base& other)
          : iterator_base(other.node) {}
      pre_order_iterator(const sibling_iterator& other)
          : iterator_base(other.node) {
        if (this->node == nullptr) {
          if (other.range_last() != nullptr) {
            this->node = other.range_last();
          } else {
            this->node = other.parent_;
          }
          this->skip_children();
          ++(*this);
        }
      }

      bool operator==(const pre_order_iterator& other) const {
        if (other.node == this->node) {
          return true;
        } else {
          return false;
        }
      }
      bool operator!=(const pre_order_iterator& other) const {
        if (other.node != this->node) {
          return true;
        } else {
          return false;
        }
      }
      pre_order_iterator& operator++() {
        assert(this->node != nullptr);
        if (!this->skip_children_ && this->node->first_child != nullptr) {
          this->node = this->node->first_child;
        } else {
          this->skip_children_ = false;
          while (this->node->next_sibling == nullptr) {
            this->node = this->node->parent;
            if (this->node == nullptr) return *this;
          }
          this->node = this->node->next_sibling;
        }
        return *this;
      }
      pre_order_iterator& operator--() {
        assert(this->node != nullptr);
        if (this->node->prev_sibling) {
          this->node = this->node->prev_sibling;
          while (this->node->last_child) this->node = this->node->last_child;
        } else {
          this->node = this->node->parent;
          if (this->node == nullptr) return *this;
        }
        return *this;
      }
      pre_order_iterator operator++(int) {
        pre_order_iterator copy = *this;
        ++(*this);
        return copy;
      }
      pre_order_iterator operator--(int) {
        pre_order_iterator copy = *this;
        --(*this);
        return copy;
      }
      pre_order_iterator& operator+=(unsigned num) {
        while (num > 0) {
          ++(*this);
          --num;
        }
        return (*this);
      }
      pre_order_iterator& operator-=(unsigned num) {
        while (num > 0) {
          --(*this);
          --num;
        }
        return (*this);
      }

      pre_order_iterator& next_skip_children() {
        (*this).skip_children();
        (*this)++;
        return *this;
      }
    };
    class post_order_iterator : public iterator_base {
     public:
      post_order_iterator() : iterator_base(nullptr) {}
      post_order_iterator(Node_* tn) : iterator_base(tn) {}
      post_order_iterator(const iterator_base& other)
          : iterator_base(other.node) {}
      post_order_iterator(const sibling_iterator& other)
          : iterator_base(other.node) {
        if (this->node == nullptr) {
          if (other.range_last() != nullptr) {
            this->node = other.range_last();
          } else {
            this->node = other.parent_;
          }
          this->skip_children();
          ++(*this);
        }
      }

      bool operator==(const post_order_iterator& other) const {
        if (other.node == this->node) {
          return true;
        } else {
          return false;
        }
      }
      bool operator!=(const post_order_iterator& other) const {
        if (other.node != this->node) {
          return true;
        } else {
          return false;
        }
      }
      post_order_iterator& operator++() {
        assert(this->node != nullptr);
        if (this->node->next_sibling == nullptr) {
          this->node = this->node->parent;
          this->skip_children_ = false;
        } else {
          this->node = this->node->next_sibling;
          if (this->skip_children_) {
            this->skip_children_ = false;
          } else {
            while (this->node->first_child)
              this->node = this->node->first_child;
          }
        }
        return *this;
      }
      post_order_iterator& operator--() {
        assert(this->node != nullptr);
        if (this->skip_children_ || this->node->last_child == nullptr) {
          this->skip_children_ = false;
          while (this->node->prev_sibling == nullptr)
            this->wnode = this->node->parent;
          this->node = this->node->prev_sibling;
        } else {
          this->node = this->node->last_child;
        }
        return *this;
      }
      post_order_iterator operator++(int) {
        post_order_iterator copy = *this;
        ++(*this);
        return copy;
      }
      post_order_iterator operator--(int) {
        post_order_iterator copy = *this;
        --(*this);
        return copy;
      }
      post_order_iterator& operator+=(unsigned num) {
        while (num > 0) {
          ++(*this);
          --num;
        }
        return (*this);
      }
      post_order_iterator& operator-=(unsigned num) {
        while (num > 0) {
          --(*this);
          --num;
        }
        return (*this);
      }

      void descend_all() {
        assert(this->node != nullptr);
        while (this->node->first_child) this->node = this->node->first_child;
      }
    };
    class breadth_first_queued_iterator : public iterator_base {
     public:
      breadth_first_queued_iterator() : iterator_base() {}
      breadth_first_queued_iterator(Node_* tn) : iterator_base(tn) {
        traversal_queue_.push(tn);
      }
      breadth_first_queued_iterator(const iterator_base& other)
          : iterator_base(other.node) {
        traversal_queue_.push(other.node);
      }

      bool operator==(const breadth_first_queued_iterator& other) const {
        if (other.node == this->node) {
          return true;
        } else {
          return false;
        }
      }
      bool operator!=(const breadth_first_queued_iterator& other) const {
        if (other.node != this->node) {
          return true;
        } else {
          return false;
        }
      }
      breadth_first_queued_iterator& operator++() {
        assert(this->node != nullptr);
        sibling_iterator sib = this->begin();
        while (sib != this->end()) {
          traversal_queue_.push(sib.node);
          ++sib;
        }
        traversal_queue_.pop();
        if (traversal_queue_.size() > 0) {
          this->node = traversal_queue_.front();
        } else {
          this->node = nullptr;
        }
        return (*this);
      }
      breadth_first_queued_iterator operator++(int) {
        breadth_first_queued_iterator copy = *this;
        ++(*this);
        return copy;
      }
      breadth_first_queued_iterator& operator+=(unsigned num) {
        while (num > 0) {
          ++(*this);
          --num;
        }
        return (*this);
      }

     private:
      std::queue<Node_*> traversal_queue_;
    };
    class fixed_depth_iterator : public iterator_base {
     public:
      fixed_depth_iterator() : iterator_base() {}
      fixed_depth_iterator(Node_* tn) : iterator_base(tn), top_node(nullptr) {}
      fixed_depth_iterator(const iterator_base& other)
          : iterator_base(other.node), top_node(nullptr) {}
      fixed_depth_iterator(const sibling_iterator& other)
          : iterator_base(other.node), top_node(nullptr) {}
      fixed_depth_iterator(const fixed_depth_iterator& other)
          : iterator_base(other.node), top_node(other.top_node) {}

      bool operator==(const fixed_depth_iterator& other) const {
        if (other.node == this->node && other.top_node == top_node) {
          return false;
        } else {
          return true;
        }
      }
      bool operator!=(const fixed_depth_iterator& other) const {
        if (other.node != this->node || other.top_node != top_node) {
          return false;
        } else {
          return true;
        }
      }
      fixed_depth_iterator& operator++() {
        assert(this->node != nullptr);
        if (this->node->next_sibling) {
          this->node = this->node->next_sibling;
        } else {
          int rel_depth = 0;
        upper:
          do {
            if (this->node == this->top_node) {
              this->node = nullptr;
              return *this;
            }
            this->node = this->node->parent;
            if (this->node == nullptr) return *this;
            --rel_depth;
          } while (this->node->next_sibling == nullptr);
        lower:
          this->node = this->node->next_sibling;
          while (this->node->first_child == nullptr) {
            if (this->node->next_sibling == nullptr) goto upper;
            this->node = this->node->next_sibling;
            if (this->node == nullptr) return *this;
          }
          while (rel_depth < 0 && this->node->first_child != nullptr) {
            this->node = this->node->first_child;
            ++rel_depth;
          }
          if (rel_depth < 0) {
            if (this->node->next_sibling == nullptr) {
              goto upper;
            } else {
              goto lower;
            }
          }
        }
        return *this;
      }
      fixed_depth_iterator& operator--() {
        assert(this->node != 0);

        if (this->node->prev_sibling) {
          this->node = this->node->prev_sibling;
        } else {
          int relative_depth = 0;
        upper:
          do {
            if (this->node == this->top_node) {
              this->node = 0;
              return *this;
            }
            this->node = this->node->parent;
            if (this->node == 0) return *this;
            --relative_depth;
          } while (this->node->prev_sibling == 0);
        lower:
          this->node = this->node->prev_sibling;
          while (this->node->last_child == 0) {
            if (this->node->prev_sibling == 0) goto upper;
            this->node = this->node->prev_sibling;
            if (this->node == 0) return *this;
          }
          while (relative_depth < 0 && this->node->last_child != 0) {
            this->node = this->node->last_child;
            ++relative_depth;
          }
          if (relative_depth < 0) {
            if (this->node->prev_sibling == 0)
              goto upper;
            else
              goto lower;
          }
        }
        return *this;
      }
      fixed_depth_iterator operator++(int) {
        fixed_depth_iterator copy = *this;
        ++(*this);
        return copy;
      }
      fixed_depth_iterator operator--(int) {
        fixed_depth_iterator copy = *this;
        --(*this);
        return copy;
      }
      fixed_depth_iterator& operator+=(unsigned num) {
        while (num > 0) {
          ++(*this);
          --num;
        }
        return *this;
      }
      fixed_depth_iterator& operator-=(unsigned num) {
        while (num > 0) {
          --(*this);
          --num;
        }
        return *this;
      }

      Node_* top_node;
    };
    class sibling_iterator : public iterator_base {
     public:
      sibling_iterator() : iterator_base() { set_parent(); }
      sibling_iterator(Node_* tn) : iterator_base(tn) { set_parent(); }
      sibling_iterator(const iterator_base& other) : iterator_base(other.node) {
        set_parent();
      }
      sibling_iterator(const sibling_iterator& other)
          : iterator_base(other), parent_(other.parent_) {}

      bool operator==(const sibling_iterator& other) const {
        if (other.node == this->node) {
          return true;
        } else {
          return false;
        }
      }
      bool operator!=(const sibling_iterator& other) const {
        if (other.node != this->node) {
          return true;
        } else {
          return false;
        }
      }
      sibling_iterator& operator++() {
        if (this->node) this->node = this->node->next_sibling;
        return *this;
      }
      sibling_iterator& operator--() {
        if (this->node) {
          this->node = this->node->prev_sibling;
        } else {
          assert(parent_);
          this->node = parent_->last_child;
        }
        return *this;
      }
      sibling_iterator operator++(int) {
        sibling_iterator copy = *this;
        ++(*this);
        return copy;
      }
      sibling_iterator operator--(int) {
        sibling_iterator copy = *this;
        --(*this);
        return copy;
      }
      sibling_iterator& operator+=(unsigned num) {
        while (num > 0) {
          ++(*this);
          --num;
        }
        return (*this);
      }
      sibling_iterator& operator-=(unsigned num) {
        while (num > 0) {
          --(*this);
          --num;
        }
        return (*this);
      }

      Node_* range_first() const { return parent_->first_child; }
      Node_* range_last() const { return parent_->last_child; }
      Node_* parent_;

     private:
      void set_parent() {
        parent_ = nullptr;
        if (this->node == nullptr) return;
        if (this->node->parent != nullptr) parent_ = this->node->parent;
      }
    };
    class leaf_iterator : public iterator_base {
     public:
      leaf_iterator() : iterator_base(nullptr), top_node_(nullptr) {}
      leaf_iterator(Node_* tn, Node_* top = 0)
          : iterator_base(tn), top_node_(top) {}
      leaf_iterator(const iterator_base& other)
          : iterator_base(other.node), top_node_(nullptr) {}
      leaf_iterator(const sibling_iterator& other)
          : iterator_base(other.node), top_node_(nullptr) {}

      bool operator==(const leaf_iterator& other) const {
        if (other.node == this->node) {
          return true;
        } else {
          return false;
        }
      }
      bool operator!=(const leaf_iterator& other) const {
        if (other.node != this->node) {
          return true;
        } else {
          return false;
        }
      }
      leaf_iterator& operator++() {
        assert(this->node != nullptr);
        if (this->node->first_child != nullptr) {
          while (this->node->first_child) this->node = this->node->first_child;
        } else {
          while (this->node->next_sibling == nullptr) {
            if (this->node->parent == nullptr) return *this;
            this->node = this->node->parent;
            if (top_node_ != nullptr && this->node == top_node_) return *this;
          }
          this->node = this->node->next_sibling;
          while (this->node->first_child) this->node = this->node->first_child;
        }
        return *this;
      }
      leaf_iterator& operator--() {
        assert(this->node != nullptr);
        while (this->node->prev_sibling == nullptr) {
          if (this->node->parent == nullptr) return *this;
          this->node = this->node->parent;
          if (top_node_ != nullptr && this->node == top_node_) return *this;
        }
        this->node = this->node->prev_sibling;
        while (this->node->last_child) this->node = this->node->last_child;
        return *this;
      }
      leaf_iterator operator++(int) {
        leaf_iterator copy = *this;
        ++(*this);
        return copy;
      }
      leaf_iterator operator--(int) {
        leaf_iterator copy = *this;
        --(*this);
        return copy;
      }
      leaf_iterator& operator+=(unsigned num) {
        while (num > 0) {
          ++(*this);
          --num;
        }
        return (*this);
      }
      leaf_iterator& operator-=(unsigned num) {
        while (num > 0) {
          --(*this);
          --num;
        }
        return (*this);
      }

     private:
      Node_* top_node_;
    };

    class iterator_base_less {
     public:
      bool operator()(
          const typename Tree<_Tp, _Al, _AlTp>::iterator_base& one,
          const typename Tree<_Tp, _Al, _AlTp>::iterator_base& two) const {
        return one.node < two.node;
      }
    };

    Tree() { head_initialise(); }
    Tree(const _Tp& val) {
      head_initialise();
      set_head(val);
    }
    Tree(const iterator_base& val) {
      head_initialise();
      set_head((*val));
      replace(begin(), val);
    }
    Tree(const Tree<_Tp, _Al>& val) {
      head_initialise();
      copy(val);
    }
    Tree(Tree<_Tp, _Al>&& val) {
      head_initialise();
      if (val.head->next_sibling != val.feet) {
        head->next_sibling = val.head->next_sibling;
        feet->next_sibling = val.head->pref_sibling;
        val.head->next_sibling->prev_sibling = head;
        val.feet->prev_sibling->next_sibling = feet;
        val.head->next_sibling = val.feet;
        val.feet->prev_sibling = val.head;
      }
    }
    ~Tree() {
      clear();
      alloc_.destroy(head);
      alloc_.destroy(feet);
      alloc_.deallocate(head, 1);
      alloc_.deallocate(feet, 1);
    }

    Tree<_Tp, _Al>& operator=(const Tree<_Tp, _Al>& val) {
      if (this != &val) {
        copy(val);
      }
      return *this;
    }
    Tree<_Tp, _Al>& operator=(Tree<_Tp, _Al>&& val) {
      if (this != &val) {
        head->next_sibling = val.head->next_sibling;
        feet->next_sibling = val.head->pref_sibling;
        val.head->next_sibling->prev_sibling = head;
        val.feet->prev_sibling->next_sibling = feet;
        val.head->next_sibling = val.feet;
        val.feet->prev_sibling = val.head;
      }
      return *this;
    }

    inline pre_order_iterator begin() const {
      return pre_order_iterator(head->next_sibling);
    }
    inline pre_order_iterator end() const { return pre_order_iterator(feet); }
    post_order_iterator begin_post() const {
      Node_* tmp = head->next_sibling;
      if (tmp != feet) {
        while (tmp->first_child) {
          tmp = tmp->first_child;
        }
      }
      return post_order_iterator(tmp);
    }
    post_order_iterator end_post() const { return post_order_iterator(feet); }
    fixed_depth_iterator begin_fixed(const iterator_base& pos,
                                     unsigned dp) const {
      fixed_depth_iterator ret;
      ret.top_node = pos.node;
      Node_* tmp = pos.node;

      unsigned int cur_depth = 0;
      while (cur_depth < dp) {
        while (tmp->first_child == nullptr) {
          if (tmp->next_sibling == nullptr) {
            do {
              if (tmp == ret.top_node) {
                throw std::range_error("tree: begin_fixed out of range");
              }
              tmp = tmp->parent;
              if (tmp == nullptr) {
                throw std::range_error("Tree: begin_fixed out of range");
              }
              --cur_depth;
            } while (tmp->next_sibling == nullptr);
          }
          tmp = tmp->next_sibling;
        }
        tmp = tmp->first_child;
        ++cur_depth;
      }
      ret.node = tmp;
      return ret;
    }
    fixed_depth_iterator end_fixed(const iterator_base& pos,
                                   unsigned dp) const {
      Node_* tmp = pos.node;
      unsigned int cur_depth = 1;
      while (cur_depth < dp) {
        while (tmp->first_child == 0) {
          tmp = tmp->next_sibling;
          if (tmp == 0) {
            throw std::range_error("Tree: end_fixed out of range");
          }
        }
        tmp = tmp->first_child;
        ++cur_depth;
      }
      return tmp;
    }
    breadth_first_queued_iterator begin_breadth_first() const {
      return breadth_first_queued_iterator(head->next_sibling);
    }
    breadth_first_queued_iterator end_breadth_first() const {
      return breadth_first_queued_iterator();
    }
    static sibling_iterator begin(const iterator_base& pos) {
      assert(pos.node != nullptr);  // FIXME
      if (pos.node->first_child == nullptr) {
        return end(pos);
      }
      return pos.node->first_child;
    }
    static sibling_iterator end(const iterator_base& pos) {
      sibling_iterator ret(0);
      ret.parent_ = pos.node;
      return ret;
    }

    leaf_iterator begin_leaf() const {
      Node_* tmp = head->next_sibling;
      if (tmp != feet) {
        while (tmp->first_child) {
          tmp = tmp->first_child;
        }
      }
      return leaf_iterator(tmp);
    }
    leaf_iterator end_leaf() const { return leaf_iterator(feet); }
    leaf_iterator begin_leaf(const iterator_base& top) const {
      Node_* tmp = top.node;
      while (tmp->first_child) {
        tmp = tmp->first_child;
      }
      return leaf_iterator(tmp, top.node);
    }
    leaf_iterator end_leaf(const iterator_base& top) const {
      return leaf_iterator(top.node, top.node);
    }

    template <typename _Iter>
    static _Iter parent(_Iter pos) {
      assert(pos.node != nullptr);  // FIXME
      return _Iter(pos.node->parent);
    }
    template <typename _Iter>
    static _Iter previous_sibling(_Iter pos) {
      assert(pos.node != nullptr);  // FIXME
      _Iter ret(pos);
      ret.node = pos.node->prev_sibling;
      return ret;
    }
    template <typename _Iter>
    static _Iter next_sibling(_Iter pos) {
      assert(pos.node != nullptr);  // FIXME
      _Iter ret(pos);
      ret.node = pos.node->next_sibling;
      return ret;
    }
    template <typename _Iter>
    _Iter next_at_same_depth(_Iter pos) const {
      fixed_depth_iterator tmp(pos.node);
      ++tmp;
      return _Iter(tmp);
    }

    void clear() {
      if (head) {
        while (head->next_sibling != feet) {
          erase(pre_order_iterator(head->next_sibling));
        }
      }
    }

    template <typename _Iter>
    _Iter erase(_Iter it) {
      Node_* cur = it.node;
      assert(cur != head);  // FIXME
      _Iter ret = it;
      ret.skip_children();
      ++ret;
      erase_children(it);
      if (cur->prev_sibling == nullptr) {
        cur->parent->first_child = cur->next_sibling;
      } else {
        cur->prev_sibling->next_sibling = cur->next_sibling;
      }
      if (cur->next_sibling == nullptr) {
        cur->parent->last_child = cur->prev_sibling;
      } else {
        cur->next_sibling->prev_sibling = cur->prev_sibling;
      }
      alloc_.destroy(cur);
      alloc_.deallocate(cur, 1);
      return ret;
    }

    void erase_children(const iterator_base& it) {
      if (it.node == nullptr) return;
      Node_* cur = it.node->first_child;
      Node_* prev = nullptr;
      while (cur != nullptr) {
        prev = cur;
        cur = cur->next_sibling;
        erase_children(pre_order_iterator(prev));
        alloc_.destroy(prev);
        alloc_.deallocate(prev, 1);
      }
      it.node->first_child = nullptr;
      it.node->last_child = nullptr;
    }
    void erase_right_siblings(const iterator_base& it) {
      if (it.node == nullptr) return;
      Node_* cur = it.node->next_sibling;
      Node_* prev = nullptr;
      while (cur != nullptr) {
        prev = cur;
        cur = cur->next_sibling;
        erase_children(pre_order_iterator(prev));
        alloc_.destroy(prev);
        alloc_.deallocate(prev, 1);
      }
      it.nod->next_sibling = nullptr;
      if (it.node->parent != 0) {
        it.node->parent->last_child = it.node;
      }
    }
    void erase_left_siblings(const iterator_base& it) {
      if (it.node == nullptr) return;
      Node_* cur = it.node->prev_sibling;
      Node_* prev = nullptr;
      while (cur != nullptr) {
        prev = cur;
        cur = cur->prev_sibling;
        erase_children(pre_order_iterator(prev));
        alloc_.destroy(prev);
        alloc_.deallocate(prev, 1);
      }
      it.nod->prev_sibling = nullptr;
      if (it.node->parent != 0) {
        it.node->parent->first_child = it.node;
      }
    }

    template <typename _Iter>
    _Iter append_child(_Iter position) {
      assert(position.node != head);  // FIXME
      assert(position.node != feet);  // FIXME
      assert(position.node);          // FIXME
      Node_* tmp = alloc_.allocate(1, 0);
      alloc_.construct(tmp, Node_());
      tmp->first_child = nullptr;
      tmp->last_child = nullptr;
      tmp->parent = position.node;
      if (position.node->last_child != nullptr) {
        position.node->last_child->next_sibling = tmp;
      } else {
        position.node->first_child = tmp;
      }
      tmp->prev_sibling = position.node->last_child;
      position.node->last_child = tmp;
      tmp->next_sibling = nullptr;
      return tmp;
    }
    template <typename _Iter>
    _Iter prepend_child(_Iter position) {
      assert(position.node != head);
      assert(position.node != feet);
      assert(position.node);

      Node_* tmp = alloc_.allocate(1, 0);
      alloc_.construct(tmp, TreeNode_<_Tp>());
      tmp->first_child = nullptr;
      tmp->last_child = nullptr;
      tmp->parent = position.node;
      if (position.node->first_child != nullptr) {
        position.node->first_child->prev_sibling = tmp;
      } else {
        position.node->last_child = tmp;
      }
      tmp->next_sibling = position.node->first_child;
      position.node->prev_child = tmp;
      tmp->prev_sibling = nullptr;
      return tmp;
    }
    template <typename _Iter>
    _Iter append_child(_Iter position, const _Tp& val) {
      assert(position.node != head);
      assert(position.node != feet);
      assert(position.node);
      Node_* tmp = alloc_.allocate(1, 0);
      alloc_.construct(tmp, val);
      tmp->first_child = nullptr;
      tmp->last_child = nullptr;
      tmp->parent = position.node;
      if (position.node->last_child != nullptr) {
        position.node->last_child->next_sibling = tmp;
      } else {
        position.node->first_child = tmp;
      }
      tmp->prev_sibling = position.node->last_child;
      position.node->last_child = tmp;
      tmp->next_sibling = nullptr;
      return tmp;
    }
    template <typename _Iter>
    _Iter append_child(_Iter position, _Tp&& val) {
      assert(position.node != head);
      assert(position.node != feet);
      assert(position.node);
      Node_* tmp = alloc_.allocate(1, 0);
      alloc_.construct(tmp);
      std::swap(tmp->data, val);
      tmp->first_child = nullptr;
      tmp->last_child = nullptr;
      tmp->parent = position.node;
      if (position.node->last_child != nullptr) {
        position.node->last_child->next_sibling = tmp;
      } else {
        position.node->first_child = tmp;
      }
      tmp->prev_sibling = position.node->last_child;
      position.node->last_child = tmp;
      tmp->next_sibling = nullptr;
      return tmp;
    }
    template <typename _Iter>
    _Iter prepend_child(_Iter position, const _Tp& val) {
      assert(position.node != head);
      assert(position.node != feet);
      assert(position.node);

      Node_* tmp = alloc_.allocate(1, 0);
      alloc_.construct(tmp, val);
      tmp->first_child = nullptr;
      tmp->last_child = nullptr;
      tmp->parent = position.node;
      if (position.node->first_child != nullptr) {
        position.node->first_child->prev_sibling = tmp;
      } else {
        position.node->last_child = tmp;
      }
      tmp->next_sibling = position.node->first_child;
      position.node->prev_child = tmp;
      tmp->prev_sibling = nullptr;
      return tmp;
    }
    template <typename _Iter>
    _Iter prepend_child(_Iter position, _Tp&& val) {
      assert(position.node != head);
      assert(position.node != feet);
      assert(position.node);

      Node_* tmp = alloc_.allocate(1, 0);
      alloc_.construct(tmp);
      std::swap(tmp->data, val);
      tmp->first_child = nullptr;
      tmp->last_child = nullptr;
      tmp->parent = position.node;
      if (position.node->first_child != nullptr) {
        position.node->first_child->prev_sibling = tmp;
      } else {
        position.node->last_child = tmp;
      }
      tmp->next_sibling = position.node->first_child;
      position.node->prev_child = tmp;
      tmp->prev_sibling = nullptr;
      return tmp;
    }

    template <typename _Iter>
    _Iter append_child(_Iter pos_a, _Iter pos_b) {
      assert(pos_a.node != head);
      assert(pos_a.node != feet);
      assert(pos_a.node);
      sibling_iterator it = append_child(pos_a, value_type());
      return replace(it, pos_b);
    }
    template <typename _Iter>
    _Iter prepend_child(_Iter pos_a, _Iter pos_b) {
      assert(pos_a.node != head);
      assert(pos_a.node != feet);
      assert(pos_a.node);
      sibling_iterator it = prepend_child(pos_a, value_type());
      return replace(it, pos_b);
    }

    template <typename _Iter>
    _Iter append_children(_Iter pos, sibling_iterator from,
                          sibling_iterator to) {
      assert(pos.node != head);
      assert(pos.node != feet);
      assert(pos.node);
      _Iter ret = from;
      while (from != to) {
        insert_subtree(pos.end(), from);
        ++from;
      }
      return ret;
    }
    template <typename _Iter>
    _Iter prepend_children(_Iter pos, sibling_iterator from,
                           sibling_iterator to) {
      assert(pos.node != head);
      assert(pos.node != feet);
      assert(pos.node);
      if (from == to) return from;

      _Iter ret;
      do {
        --to;
        ret = insert_subtree(pos.begin(), to);
      } while (to != from);
      return ret;
    }

    pre_order_iterator set_head(const _Tp& val) {
      assert(head->next_sibling == feet);
      return insert(iterator(feet), val);
    }
    pre_order_iterator set_head(_Tp&& val) {
      assert(head->next_sibling == feet);
      return insert(iterator(feet), val);
    }

    template <typename _Iter>
    _Iter insert(_Iter pos, const _Tp& val) {
      if (pos.node == nullptr) {
        pos.node = feet;
      }
      assert(pos.node != head);
      Node_* tmp = alloc_.allocate(1, 0);
      alloc_.construct(tmp, val);
      tmp->first_child = nullptr;
      tmp->last_child = nullptr;
      tmp->parent = pos.node->parent;
      tmp->next_sibling = pos.node;
      tmp->prev_sibling = pos.node->prev_sibling;
      pos.node->prev_sibling = tmp;
      if (tmp->prev_sibling == nullptr) {
        if (tmp->parent) {
          tmp->parent->first_child = tmp;
        }
      } else {
        tmp->prev_sibling->next_sibling = tmp;
      }
      return tmp;
    }
    template <typename _Iter>
    _Iter insert(_Iter pos, _Tp&& val) {
      if (pos.node == nullptr) {
        pos.node = feet;
      }
      assert(pos.node != head);
      Node_* tmp = alloc_.allocate(1, 0);
      alloc_.construct(tmp);
      std::swap(tmp->data, val);
      tmp->first_child = nullptr;
      tmp->last_child = nullptr;
      tmp->parent = pos.node->parent;
      tmp->next_sibling = pos.node;
      tmp->prev_sibling = pos.node->prev_sibling;
      pos.node->prev_sibling = tmp;
      if (tmp->prev_sibling == nullptr) {
        if (tmp->parent) {
          tmp->parent->first_child = tmp;
        }
      } else {
        tmp->prev_sibling->next_sibling = tmp;
      }
      return tmp;
    }
    sibling_iterator insert(sibling_iterator pos, const _Tp& val) {
      Node_* tmp = alloc_.allocate(1, 0);
      alloc_.construct(tmp, val);
      tmp->first_child = nullptr;
      tmp->last_child = nullptr;
      tmp->next_sibling = pos.node;
      if (pos.node == nullptr) {
        tmp->parent = pos.parent_;
        tmp->prev_sibling = pos.range_last();
        tmp->parent->last_child = tmp;
      } else {
        tmp->parent = pos.node->parent;
        tmp->prev_sibling = pos.node->prev_sibling;
        pos.node->prev_sibling = tmp;
      }
      if (tmp->prev_sibling == nullptr) {
        if (tmp->parent) {
          tmp->parent->first_child = tmp;
        }
      } else {
        tmp->prev_sibling->next_sibling = tmp;
      }
      return tmp;
    }

    template <typename _Iter>
    _Iter insert_after(_Iter pos, const _Tp& val) {
      Node_* tmp = alloc_.allocate(1, 0);
      alloc_.construct(tmp, val);
      tmp->first_child = nullptr;
      tmp->last_child = nullptr;
      tmp->parent = pos.node->parent;
      tmp->next_sibling = pos.node->next_sibling;
      tmp->prev_sibling = pos.node;
      pos.node->next_sibling = tmp;
      if (tmp->next_sibling == nullptr) {
        if (tmp->parent) {
          tmp->parent->last_child = tmp;
        }
      } else {
        tmp->next_sibling->prev_sibling = tmp;
      }
      return tmp;
    }
    template <typename _Iter>
    _Iter insert_after(_Iter pos, _Tp&& val) {
      Node_* tmp = alloc_.allocate(1, 0);
      alloc_.construct(tmp);
      std::swap(tmp->data, val);
      tmp->first_child = nullptr;
      tmp->last_child = nullptr;
      tmp->parent = pos.node->parent;
      tmp->next_sibling = pos.node->next_sibling;
      tmp->prev_sibling = pos.node;
      pos.node->next_sibling = tmp;
      if (tmp->next_sibling == nullptr) {
        if (tmp->parent) {
          tmp->parent->last_child = tmp;
        }
      } else {
        tmp->next_sibling->prev_sibling = tmp;
      }
      return tmp;
    }

    template <typename _Iter>
    _Iter insert_subtree(_Iter pos, const iterator_base& subtree) {
      _Iter it = insert(pos, value_type());
      return replace(it, subtree);
    }
    template <typename _Iter>
    _Iter insert_subtree_after(_Iter pos, const iterator_base& subtree) {
      _Iter it = insert_after(pos, value_type());
      return replace(it, subtree);
    }

    template <typename _Iter>
    _Iter replace(_Iter pos, const _Tp& val) {
      pos.node->data = val;
      return pos;
    }
    template <typename _Iter>
    _Iter replace(_Iter pos, const iterator_base& from) {
      assert(pos.node != head);
      Node_ *current_from = from.node, *start_from = from.node,
            *current_to = pos.node;
      erase_children(pos);
      Node_* tmp = alloc_.allocate(1, 0);
      alloc_.construct(tmp, (*from));
      tmp->first_child = nullptr;
      tmp->last_child = nullptr;
      if (current_to->prev_sibling == nullptr) {
        if (current_to->parent != nullptr) {
          current_to->parent->first_child = tmp;
        }
      } else {
        current_to->prev_sibling->next_sibling = tmp;
      }
      if (current_to->next_sibling == nullptr) {
        if (current_to->parent != nullptr) {
          current_to->parent->last_child = tmp;
        }
      } else {
        current_to->next_sibling->prev_sibling = tmp;
      }
      tmp->prev_sibling = current_to->prev_sibling;
      tmp->next_sibling = current_to->next_sibling;
      tmp->parent = current_to->parent;
      alloc_.destroy(current_to);
      alloc_.deallocate(current_to, 1);
      current_to = tmp;
      Node_* last = from.node->next_sibling;
      pre_order_iterator it = tmp;

      do {
        assert(current_from != nullptr);
        if (current_from->first_child != nullptr) {
          current_from = current_from->first_child;
          it = append_child(it, current_from->data);
        } else {
          while (current_from->next_sibling == nullptr &&
                 current_from != start_from) {
            current_from = current_from->parent;
            it = parent(it);
            assert(current_from != nullptr);
          }
          current_from = current_from->next_sibling;
          if (current_from != last) {
            it = append_child(parent(it), current_from->data);
          }
        }
      } while (current_from != last);
      return current_to;
    }

    sibling_iterator replace(sibling_iterator orig_begin,
                             sibling_iterator orig_end,
                             sibling_iterator new_begin,
                             sibling_iterator new_end) {
      Node_ *orig_first = orig_begin.node, new_first = new_begin.node,
            orig_last = orig_first, new_last = new_first;
      while ((++orig_begin) != orig_end) {
        orig_last = orig_last->next_sibling;
      }
      while ((++new_begin) != new_end) {
        new_last = new_last->next_sibling;
      }
      bool first = true;
      pre_order_iterator ret;
      while (true) {
        pre_order_iterator it = insert_subtree(pre_order_iterator(orig_first),
                                               pre_order_iterator(new_first));
        if (first) {
          ret = it;
          first = false;
        }
        if (new_first == new_last) break;
        new_first = new_first->next_sibling;
      }

      bool last = false;
      Node_* next = orig_first;
      while (true) {
        if (next == orig_last) last = true;
        next = next->next_sibling;
        erase((pre_order_iterator)orig_first);
        if (last) break;
        orig_first = next;
      }
      return ret;
    }

    template <typename _Iter>
    _Iter flatten(_Iter pos) {
      if (pos.node->first_child == nullptr) return pos;
      Node_* tmp = pos.node->first_child;
      while (tmp) {
        tmp->parent = pos.node->parent;
        tmp = tmp->next_sibling;
      }
      if (pos.node->next_sibling) {
        pos.node->last_child->next_sibling = pos.node->next_sibling;
        pos.node->next_sibling->prev_sibling = pos.node->last_child;
      } else {
        pos.node->parent->last_child = pos.node->last_child;
      }
      pos.node->next_sibling = pos.node->first_child;
      pos.node->next_sibling->prev_sibling = pos.node;
      pos.node->first_child = nullptr;
      pos.node->last_child = nullptr;
      return pos;
    }

    template <typename _Iter>
    _Iter reparent(_Iter pos, sibling_iterator begin, sibling_iterator end) {
      Node_* first = begin.node;
      Node_* last = first;
      assert(first != pos.node);
      if (begin == end) return begin;
      while ((++begin) != end) {
        last = last->next_sibling;
      }
      if (first->prev_sibling == nullptr) {
        first->parent->first_child = last->next_sibling;
      } else {
        first->prev_sibling->next_sibling = last->next_sibling;
      }
      if (last->next_sibling == nullptr) {
        last->parent->last_child = first->prev_sibling;
      } else {
        last->next_sibling->prev_sibling = first->prev_sibling;
      }
      if (pos.node->first_child == nullptr) {
        pos.node->first_child = first;
        pos.node->last_child = last;
        first->prev_sibling = nullptr;
      } else {
        pos.node->last_child->next_sibling = first;
        first->prev_sibling = pos.node->last_child;
        pos.node->last_child = last;
      }
      last->next_sibling = nullptr;

      Node_* position = first;
      while (true) {
        position->partent = pos.node;
        if (position == last) {
          break;
        }
        position = position->next_sibling;
      }
      return first;
    }
    template <typename _Iter>
    _Iter reparent(_Iter pos, _Iter from) {
      if (from.node->first_child == nullptr) return pos;
      return reparent(pos, from.node->first_child, end(from));
    }

    template <typename _Iter>
    _Iter wrap(_Iter pos, const _Tp& val) {
      assert(pos.node != nullptr);
      sibling_iterator from = pos, to = pos;
      ++to;
      _Iter ret = insert(pos, val);
      reparent(ret, from, to);
      return ret;
    }
    template <typename _Iter>
    _Iter wrap(_Iter from, _Iter to, const _Tp& val) {
      assert(from.node != nullptr);
      _Iter ret = insert(from, val);
      reparent(ret, from, to);
      return ret;
    }

    template <typename _Iter>
    _Iter move_after(_Iter target, _Iter source) {
      Node_* dest = target.node;
      Node_* src = source.node;
      assert(dest);
      assert(src);

      if (dest == src) return source;
      if (dest->next_sibling) {
        if (dest->next_sibling == src) {
          return source;
        }
      }
      if (src->prev_sibling != nullptr) {
        src->prev_sibling->next_sibling = src->next_sibling;
      } else {
        src->parent->first_child = src->next_sibling;
      }
      if (src->next_sibling != nullptr) {
        src->next_sibling->prev_sibling = src->prev_sibling;
      } else {
        src->parent->last_child = src->prev_sibling;
      }
      if (dest->next_sibling != nullptr) {
        dest->next_sibling->prev_sibling = src;
      } else {
        dest->parent->last_child = src;
      }
      src->next_sibling = dest->next_sibling;
      dest->next_sibling = src;
      src->prev_sibling = dest;
      src->parent = dest->parent;
      return src;
    }
    template <typename _Iter>
    _Iter move_before(_Iter target, _Iter source) {
      Node_* dest = target.node;
      Node_* src = source.node;
      assert(dest);
      assert(src);
      if (dest == src) return source;
      if (dest->prev_sibling) {
        if (dest->prev_sibling == src) {
          return source;
        }
      }
      if (src->prev_sibling != nullptr) {
        src->prev_sibling->next_sibling = src->next_sibling;
      } else {
        src->parent->first_child = src->next_sibling;
      }
      if (src->next_sibling != nullptr) {
        src->next_sibling->prev_sibling == src->prev_sibling;
      } else {
        src->parent->last_child = src->prev_sibling;
      }
      if (dest->prev_sibling != nullptr) {
        dest->prev_sibling->next_sibling = src;
      } else {
        dest->parent->first_child = src;
      }
      src->prev_sibling = dest->prev_sibling;
      dest->prev_sibling = src;
      src->next_sibling = dest;
      src->parent = dest->parent;
      return src;
    }
    sibling_iterator move_before(sibling_iterator target,
                                 sibling_iterator source) {
      Node_* dest = target.node;
      Node_* src = source.node;
      Node_* dest_prev_sibling;
      if (dest == nullptr) {
        dest_prev_sibling = target.parent_->last_child;
        assert(dest_prev_sibling);
      } else {
        dest_prev_sibling = dest->prev_sibling;
      }
      assert(src);

      if (dest == src) return source;
      if (dest_prev_sibling) {
        if (dest_prev_sibling == src) {
          return source;
        }
      }
      if (src->prev_sibling != nullptr) {
        src->prev_sibling->next_sibling = src->next_sibling;
      } else {
        src->parent->first_child = src->next_sibling;
      }
      if (src->next_sibling != nullptr) {
        src->next_sibling->prev_sibling = src->prev_sibling;
      } else {
        src->parent->last_child = src->prev_sibling;
      }

      if (dest_prev_sibling != nullptr) {
        dest_prev_sibling->next_sibling = src;
      } else {
        target.parent_->first_child = src;
      }
      src->prev_sibling = dest_prev_sibling;
      if (dest) {
        dest->prev_sibling = src;
        src->parent = dest->parent;
      }
      src->next_sibling = dest;
      return dest;
    }

    template <typename _Iter>
    _Iter move_ontop(_Iter target, _Iter source) {
      Node_* dest = target.node;
      Node_* src = source.node;
      assert(dest);
      assert(src);
      if (dest == src) return source;

      Node_* b_prev = dest->prev_sibling;
      Node_* b_next = dest->next_sibling;
      Node_* b_parent = dest->parent;

      erase(target);

      if (src->prev_sibling != nullptr) {
        src->prev_sibling->next_sibling = src->next_sibling;
      } else {
        src->parent->first_child = src->next_sibling;
      }
      if (src->next_sibling != nullptr) {
        src->next_sibling->prev_sibling = src->prev_sibling;
      } else {
        src->parent->last_child = src->prev_sibling;
      }
      if (b_prev != nullptr) {
        b_prev->next_sibling = src;
      } else {
        b_parent->first_child = src;
      }
      if (b_next != nullptr) {
        b_next->prev_sibling = src;
      } else {
        b_parent->last_child = src;
      }
      src->prev_sibling = b_prev;
      src->next_sibling = b_next;
      src->parent = b_parent;
      return src;
    }

    Tree move_out(iterator src) {
      Tree ret;
      ret.head->next_sibling = src.node;
      ret.feet->prev_sibling = src.node;
      src.node->parent = nullptr;

      if (src.node->prev_sibling != nullptr) {
        src.node->prev_sibling->next_sibling = src.node->next_sibling;
      }
      if (src.node->next_sibling != nullptr) {
        src.node->next_sibling->prev_sibling = src.node->prev_sibling;
      }
      src.node->prev_sibling = ret.head;
      src.node->next_sibling = ret.feet;
      return ret;
    }

    template <typename _Iter>
    _Iter move_in(_Iter loc, Tree& other) {
      if (other.head->next_sibling == other.feet) return loc;
      Node_* other_first = other.head->next_sibling;
      Node_* other_last = other.feet->pref_sibling;
      sibling_iterator prev(loc);
      --prev;
      prev.node->next_sibling = other_first;
      loc.node->prev_sibling = other_last;
      Node_* walk = other_first;

      while (true) {
        walk->parent = loc.node->parent;
        if (walk == other_last) break;
        walk = walk->next_sibling;
      }
      other.head->next_sibling = other.feet;
      other.feet->prev_sibling = other.head;
      return other_first;
    }

    template <typename _Iter>
    _Iter move_in_as_nth_child(_Iter loc, std::size_t n, Tree& other) {
      if (other.head->next_sibling == other.feet) return loc;

      Node_* other_first_head = other.head->next_sibling;
      Node_* other_last_head = other.feet->prev_sibling;

      if (n == 0) {
        if (loc.node->first_child == 0) {
          loc.node->first_child = other_first_head;
          loc.node->last_child = other_last_head;
          other_last_head->next_sibling = 0;
          other_first_head->prev_sibling = 0;
        } else {
          loc.node->first_child->prev_sibling = other_last_head;
          other_last_head->next_sibling = loc.node->first_child;
          loc.node->first_child = other_first_head;
          other_first_head->prev_sibling = 0;
        }
      } else {
        --n;
        Node_* walk = loc.node->first_child;
        while (true) {
          if (walk == 0)
            throw std::range_error(
                "Tree: move_in_as_nth_child position out of range");
          if (n == 0) break;
          --n;
          walk = walk->next_sibling;
        }
        if (walk->next_sibling == 0)
          loc.node->last_child = other_last_head;
        else
          walk->next_sibling->prev_sibling = other_last_head;
        other_last_head->next_sibling = walk->next_sibling;
        walk->next_sibling = other_first_head;
        other_first_head->prev_sibling = walk;
      }

      Node_* walk = other_first_head;
      while (true) {
        walk->parent = loc.node;
        if (walk == other_last_head) break;
        walk = walk->next_sibling;
      }

      other.head->next_sibling = other.feet;
      other.feet->prev_sibling = other.head;

      return other_first_head;
    }

    void merge(sibling_iterator to1, sibling_iterator to2,
               sibling_iterator from1, sibling_iterator from2,
               bool duplicate_leaves = false) {
      sibling_iterator fnd;
      while (from1 != from2) {
        if ((fnd = std::find(to1, to2, (*from1))) != to2) {
          if (from1.begin() == from1.end()) {
            if (duplicate_leaves) append_child(parent(to1), (*from1));
          } else {
            merge(fnd.begin(), fnd.end(), from1.begin(), from1.end(),
                  duplicate_leaves);
          }
        } else {
          insert_subtree(to2, from1);
        }
        ++from1;
      }
    }
    void sort(sibling_iterator from, sibling_iterator to, bool deep = false) {
      std::less<_Tp> comp;
      sort(from, to, comp, deep);
    }
    template <class _Comp>
    void sort(sibling_iterator from, sibling_iterator to, _Comp comp,
              bool deep = false) {
      if (from == to) return;
      std::multiset<Node_*, compare_nodes<_Comp>> nodes(comp);
      sibling_iterator it = from, it2 = to;
      while (it != to) {
        nodes.insert(it.node);
        ++it;
      }
      --it2;

      Node_* prev = from.node->prev_sibling;
      Node_* next = it2.node->next_sibling;
      typename std::multiset<Node_*, compare_nodes<_Comp>>::iterator
          nit = nodes.begin(),
          eit = nodes.end();
      if (prev == 0) {
        if ((*nit)->parent != 0) (*nit)->parent->first_child = (*nit);
      } else
        prev->next_sibling = (*nit);

      --eit;
      while (nit != eit) {
        (*nit)->prev_sibling = prev;
        if (prev) prev->next_sibling = (*nit);
        prev = (*nit);
        ++nit;
      }
      if (prev) prev->next_sibling = (*eit);

      (*eit)->next_sibling = next;
      (*eit)->prev_sibling = prev;
      if (next == 0) {
        if ((*eit)->parent != 0) (*eit)->parent->last_child = (*eit);
      } else
        next->prev_sibling = (*eit);

      if (deep) {
        sibling_iterator bcs(*nodes.begin());
        sibling_iterator ecs(*eit);
        ++ecs;
        while (bcs != ecs) {
          sort(begin(bcs), end(bcs), comp, deep);
          ++bcs;
        }
      }
    }

    template <typename _Iter>
    bool equal(const _Iter& one, const _Iter& two, const _Iter& three) const {
      std::equal_to<_Tp> comp;
      return equal(one, two, three, comp);
    }
    template <typename _Iter, class _Bp>
    bool equal(const _Iter& one, const _Iter& two, const _Iter& three,
               _Bp comp) const {
      pre_order_iterator one_(one), three_(three);
      while (one_ != two && is_valid(three_)) {
        if (!comp(*one_, *three_)) return false;
        if (one_.number_of_children() != three_.number_of_children())
          return false;
        ++one_;
        ++three_;
      }
      return true;
    }
    template <typename _Iter>
    bool equal_subtree(const _Iter& one, const _Iter& two) const {
      std::equal_to<_Tp> comp;
      return equal_subtree(one, two, comp);
    }
    template <typename _Iter, class _Bp>
    bool equal_subtree(const _Iter& one, const _Iter& two, _Bp comp) const {
      pre_order_iterator one_(one), two_(two);
      if (!comp(*one_, *two_)) return false;
      if (number_of_children(one) != number_of_children(two)) return false;
      return equal(begin(one), end(one, begin(two), comp));
    }

    Tree<_Tp> subtree(sibling_iterator from, sibling_iterator to) const {
      assert(from != to);
      Tree<_Tp> tmp;
      tmp.set_head(value_type());
      tmp.replace(tmp.begin(), tmp.end(), from, to);
      return tmp;
    }
    void subtree(Tree& tmp, sibling_iterator from, sibling_iterator to) const {
      assert(from != to);
      tmp.set_head(value_type());
      tmp.replace(tmp.begin(), tmp.end(), from, to);
    }

    void swap(sibling_iterator it) {
      Node_* nxt = it.node->next_sibling;
      if (nxt) {
        if (it.node->prev_sibling) {
          it.node->prev_sibling->next_sibling = nxt;
        } else {
          it.node->parent->first_child = nxt;
        }
        nxt->prev_sibling = it.node->prev_sibling;
        Node_* nxtnxt = nxt->next_sibling;
        if (nxtnxt) {
          nxtnxt->prev_sibling = it.node;
        } else {
          it.node->parent->last_child = it.node;
        }
        nxt->next_sibling = it.node;
        it.node->prev_sibling = nxt;
        it.node->next_sibling = nxtnxt;
      }
    }

    void swap(iterator one, iterator two) {
      if (one.node->next_sibling == two.now) {
        swap(one);
      } else if (two.node->next_sibling == one.node) {
        swap(two);
      } else {
        Node_* nxt1 = one.node->next_sibling;
        Node_* nxt2 = two.node->next_sibling;
        Node_* prev1 = one.node->prev_sibling;
        Node_* prev2 = two.node->prev_sibling;
        Node_* par1 = one.node->parent;
        Node_* par2 = two.node->parent;
        one.node->parent = par2;
        one.node->next_sibling = nxt2;
        if (nxt2) {
          nxt2->prev_sibling = one.node;
        } else {
          par2->last_child = one.node;
        }
        one.node->prev_sibling = prev2;
        if (prev2) {
          prev2->next_sibling = one.node;
        } else {
          par2->first_child = one.node;
        }
        two.node->parent = par1;
        two.node->next_sibling = nxt1;
        if (nxt1) {
          nxt1->prev_sibling = two.node;
        } else {
          par2->last_child = two.node;
        }
        two.node->prev_sibling = prev1;
        if (prev1) {
          prev1->next_sibling = two.node;
        } else {
          par1->first_child = two.node;
        }
      }
    }

    std::size_t size() const {
      std::size_t i = 0;
      pre_order_iterator it = begin(), eit = end();
      while (it != eit) {
        ++i;
        ++it;
      }
      return i;
    }
    std::size_t size(const iterator_base& top) const {
      std::size_t i = 0;
      pre_order_iterator it = top, eit = top;
      eit.skip_children();
      ++eit;
      while (it != eit) {
        ++i;
        ++it;
      }
      return i;
    }

    bool empty() const {
      pre_order_iterator it = begin(), eit = end();
      return (it == eit);
    }

    static int depth(const iterator_base& it) {
      Node_* pos = it.node;
      assert(pos != nullptr);
      int ret = 0;
      while (pos->parent != nullptr) {
        pos = pos->parent;
        ++ret;
      }
      return ret;
    }
    static int depth(const iterator_base& it, const iterator_base& root) {
      Node_* pos = it.node;
      assert(pos != nullptr);
      int ret = 0;
      while (pos->parent != nullptr && pos != root.node) {
        pos = pos->parent;
        ++ret;
      }
      return ret;
    }

    int max_depth() const {
      int maxd = -1;
      for (Node_* it = head->next_sibling; it != feet; it = it->next_sibling) {
        maxd = std::max(maxd, max_depth(it));
      }
      return maxd;
    }
    int max_depth(const iterator_base& pos) const {
      Node_* tmp = pos.node;
      if (tmp == nullptr || tmp == head || tmp == feet) {
        return -1;
      }
      int cur_depth = 0, max_depth = 0;
      while (true) {
        while (tmp->first_child == 0) {
          if (tmp == pos.node) {
            return max_depth;
          } else if (tmp->next_sibling == nullptr) {
            do {
              tmp = tmp->parent;
              if (tmp == nullptr) {
                return max_depth;
              }
              --cur_depth;

            } while (tmp->next_sibling == nullptr);
          }
          tmp = tmp->first_child;
          ++cur_depth;
          max_depth = std::max(cur_depth, max_depth);
        }
      }
    }

    static unsigned number_of_children(const iterator_base& it) {
      Node_* pos = it.node->first_child;
      if (pos == nullptr) {
        return 0;
      }
      unsigned ret = 1;
      while ((pos = pos->next_sibling)) ++ret;
      return ret;
    }

    unsigned int number_of_siblings(const iterator_base& it) const {
      Node_* pos = it.node;
      unsigned ret = 0;
      while (pos->next_sibling && pos->next_sibling != head &&
             pos->next_sibling != feet) {
        ++ret;
        pos = pos->next_sibling;
      }
      pos = it.node;
      while (pos->prev_sibling && pos->prev_sibling != head &&
             pos->prev_sibling != feet) {
        ++ret;
        pos = pos->prev_sibling;
      }
      return ret;
    }

    bool is_in_subtree(const iterator_base& pos, const iterator_base& begin,
                       const iterator_base& end) const {
      pre_order_iterator tmp = begin;
      while (tmp != end) {
        if (tmp == pos) {
          return true;
        }
        ++tmp;
      }
      return false;
    }

    bool is_valid(const iterator_base& it) const {
      if (it.node == nullptr || it.node == feet || it.node == head) {
        return false;
      } else {
        return true;
      }
    }

    static bool is_head(const iterator_base& it) {
      if (it.node->parent == nullptr) {
        return true;
      } else {
        return false;
      }
    }

    iterator lowest_common_ancestor(const iterator_base& one,
                                    const iterator_base& two) const {
      std::set<iterator, iterator_base_less> parents;
      iterator walk = one;
      do {
        walk = parent(walk);
        parents.insert(walk);
      } while (is_valid(parent(walk)));
      walk = two;
      do {
        walk = parent(walk);
        if (parents.find(walk) != parents.end()) break;
      } while (is_valid(parent(walk)));
      return walk;
    }
    unsigned int index(sibling_iterator it) const {
      unsigned ind = 0;
      if (it.node->parent == nullptr) {
        while (it.node->prev_sibling != head) {
          it.node = it.node->prev_sibling;
          ++ind;
        }
      } else {
        while (it.node->prev_sibling != nullptr) {
          it.node = it.node->prev_sibling;
          ++ind;
        }
      }
      return ind;
    }
    static sibling_iterator child(const iterator_base& pos, unsigned int num) {
      Node_* tmp = pos.node->first_child;
      while (num--) {
        assert(tmp != nullptr);
        tmp = tmp->next_sibling;
      }
      return tmp;
    }
    sibling_iterator sibling(const iterator_base& pos, unsigned int num) const {
      Node_* tmp;
      if (pos.node->parent == nullptr) {
        tmp = head->next_sibling;
        while (num) {
          tmp = tmp->next_sibling;
          --num;
        }
      } else {
        tmp = pos.node->parent->first_child;
        while (num) {
          assert(tmp != nullptr);
          tmp = tmp->next_sibling;
          --num;
        }
      }
      return tmp;
    }

    Node_ *head, *feet;

   private:
    template <class _Comp>
    class compare_nodes {
     public:
      compare_nodes(_Comp comp) : comp_(comp){};
      bool operator()(const Node_* a, const Node_* b) {
        return comp_(a->data, b->data);
      }

     private:
      _Comp comp_;
    };

    _Al alloc_;
    void head_initialise() {
      head = alloc_.allocate(1, 0);
      feet = alloc_.allocate(1, 0);
      alloc_.construct(head, TreeNode_<_Tp>());
      alloc_.construct(feet, TreeNode_<_Tp>());

      head->parent = nullptr;
      head->first_child = nullptr;
      head->last_child = nullptr;
      head->prev_sibling = nullptr;
      head->next_sibling = feet;

      feet->parent = nullptr;
      feet->first_child = nullptr;
      feet->last_child = nullptr;
      feet->prev_sibling = head;
      feet->next_sibling = nullptr;
    }
    void copy(const Tree<_Tp, _Al, _AlTp>& other) {
      clear();
      pre_order_iterator it = other.begin(), to = begin();
      while (it != other.end()) {
        to = insert(to, (*it));
        it.skip_children();
        ++it;
      }
      to = begin();
      it = other.begin();
      while (it != other.end()) {
        to = replace(to, it);
        to.skip_children();
        it.skip_children();
        ++to;
        ++it;
      }
    }
  };

  template <typename _Tp>
  std::string PrintSubTree(Tree<_Tp> lhs, typename Tree<_Tp>::iterator i) {
    std::string ret;
    std::stringstream ss;
    if (lhs.empty()) return std::string();
    if (lhs.number_of_children(i) == 0) {
      ss<< *i;
      ret += ss.str();
    } else {
      ss << *i;
      ret += ss.str();
      ret += "(";
      int sibling_count = lhs.number_of_siblings(lhs.begin(i));
      int sibling_num;
      typename Tree<_Tp>::sibling_iterator it;
      for (it = lhs.begin(i), sibling_num = 0; it != lhs.end(i);
           ++it, ++sibling_num) {
        ret += PrintSubTree(lhs, it);
        if (sibling_num != sibling_count) {
          ret += ", ";
        }
      }
      ret += ")";
    }
    return ret;
  }
  template <typename _Tp>
  std::string PrintTree(Tree<_Tp> lhs) {
    std::string ret;
    int head_count = lhs.number_of_siblings(lhs.begin());
    int head_num = 0;
    for (typename Tree<_Tp>::sibling_iterator i = lhs.begin(); i != lhs.end();
         ++i, ++head_num) {
      ret += PrintSubTree(lhs, i);
      if (head_num != head_count) {
        ret += "\n";
      }
    }
    return ret;
  }

  template <typename _Tp>
  std::ostream& operator<<(std::ostream& out, Tree<_Tp> lhs) {
    out << PrintTree(lhs);
    return out;
  }
}  // namespace tree
}  // namespace estl

#endif  // ESTL_TREE_HPP_
