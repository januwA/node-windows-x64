#pragma once

#include <iostream>
#include <vector>

enum class NT
{
  HEX,
  UNARY,
  BINARY,
  POINTER,
  IDENTS
};

class BaseNode
{
public:
  virtual ~BaseNode() {}
  virtual NT id() = 0;
};

class IdentsNode : public BaseNode
{
public:
  std::vector<std::string *> *idents;
  IdentsNode(std::vector<std::string *> *idents) : idents(idents)
  {
  }

  ~IdentsNode()
  {
    for (auto str : *idents)
      delete str;
    delete idents;
  }

  NT id()
  {
    return NT::IDENTS;
  }
};

class HexNode : public BaseNode
{
public:
  std::string *value;
  HexNode(std::string *value) : value(value) {}
  ~HexNode()
  {
    delete value;
  }
  NT id()
  {
    return NT::HEX;
  }
};

class UnaryNode : public BaseNode
{
public:
  int op;
  BaseNode *node;
  UnaryNode(int op, BaseNode *node) : op(op), node(node) {}

  ~UnaryNode()
  {
    delete node;
  }

  NT id()
  {
    return NT::UNARY;
  }
};

class BinaryNode : public BaseNode
{
public:
  BaseNode *left;
  int op;
  BaseNode *right;
  BinaryNode(BaseNode *left, int op, BaseNode *right)
      : left(left), op(op), right(right) {}
  ~BinaryNode()
  {
    delete left;
    delete right;
  }

  NT id()
  {
    return NT::BINARY;
  }
};

class PointerNode : public BaseNode
{
public:
  BaseNode *node;
  PointerNode(BaseNode *node) : node(node) {}
  ~PointerNode()
  {
    delete node;
  }
  NT id()
  {
    return NT::POINTER;
  }
};
