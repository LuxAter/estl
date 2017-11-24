.. default-domain:: cpp

Matrix
======

.. code-block:: cpp

   #include <estl/matrix.hpp>

This file provides a two dimensional matrix container class, along with basic
matrix operations.

Class Documentation
-------------------

.. cpp:class:: template<typename _Tp, std::size_t _Nr, std::size_t _Nc, typename\
           _Al = std::allocator<_Tp>> matrix

   A standard container for storing a fixed size matrix of elements.

   ``estl::matrix`` is a container that encapsulates fixed size matrices. This
   container is an aggregated type with the same semantics as a struct holding
   a C-style array ``T[N]`` as its only non-static data member. Unlike a
   C-style array, it dosen't decay to ``T*`` automatically. Elements of this
   container can be referenced with a single index, but more commonly are
   referenced with multiple indecies.

   :tparam _Tp: Type of element. Required to be a complete type.
   :tparam _Nr: Number of rows of elements.
   :tparam _Nc: Number of columns of elements.
   :tparam _Al: Allocator type, not necessary in most situations.

   .. type:: _Al allocator_type
   .. type:: typename _Al::valuetype value_type
   .. type:: typename _Al::reference reference 
   .. type:: typename _Al::const_referene const_reference
   .. type:: typename _Al::difference_type difference_type
   .. type:: typename _Al::size_type size_type
   .. type:: typename _Al::pointer pointer
   .. type:: typename _Al::const_pointer const_pointer
   .. type:: typename _Al::pointer iterator
   .. type:: typename _Al::const_pointer const_iterator
   .. type:: std::reverse_iterator<iterator> reverse_iterator
   .. type:: std::reverse_iterator<const_iterator> const_reverse_iterator

Constructors
^^^^^^^^^^^^

.. cpp:function:: matrix::matrix()

   Default matrix constructor.

   This allocates the memory required for the desired matrix, and fills the
   elements with ``_Tp()``.

.. cpp:function:: matrix::matrix()

   Matrix Constructor.

   Allocates the memory required for the matrix, and copies the elements of the
   initializer list to the elements of the matrix.

   :throws out_of_range: Throw out of range if the size of ``mat`` is
                         greater than the size of the matrix.

   :param mat: list of elements to copy into the matrix.

.. cpp:function:: matrix::matrix()

   Matrix Constructor.

   Allocates the memory required for the matrix, and copies the elements of the
   two dimensional initializer list to the elements of the matrix.

   :throws out_of_range: If ``mat`` is greater than ``_Nr``.
   :throws out_of_range: If ``mat[i]`` is greater than ``_Nc``.
