#pragma once

#include <iostream>
#include <vector>
#include "location.hh"

namespace ces
{
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
    ces::location loc;
    BaseNode(ces::location loc) : loc(loc){};
    virtual ~BaseNode() = default;
    virtual NT id() const = 0;
  };

  class IdentsNode : public BaseNode
  {
  public:
    std::vector<std::string> *idents;
    IdentsNode(std::vector<std::string> *idents, const ces::location &loc) : BaseNode(loc), idents(idents)
    {
    }

    ~IdentsNode()
    {
      delete idents;
    }

    NT id() const override
    {
      return NT::IDENTS;
    }
  };

  class HexNode : public BaseNode
  {
  public:
    std::string value;
    HexNode(std::string value, const ces::location &loc) : BaseNode(loc), value(value) {}
    ~HexNode()
    {
    }
    NT id() const override
    {
      return NT::HEX;
    }
  };

  class UnaryNode : public BaseNode
  {
  public:
    int op;
    BaseNode *node;
    UnaryNode(int op, BaseNode *node, const ces::location &loc) : BaseNode(loc), op(op), node(node) {}

    ~UnaryNode()
    {
      delete node;
    }

    NT id() const override
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
    BinaryNode(BaseNode *left, int op, BaseNode *right, const ces::location &loc)
        : BaseNode(loc), left(left), op(op), right(right) {}
    ~BinaryNode()
    {
      delete left;
      delete right;
    }

    NT id() const override
    {
      return NT::BINARY;
    }
  };

  class PointerNode : public BaseNode
  {
  public:
    BaseNode *node;
    PointerNode(BaseNode *node, const ces::location &loc) : BaseNode(loc), node(node) {}
    ~PointerNode()
    {
      delete node;
    }
    NT id() const override
    {
      return NT::POINTER;
    }
  };
}
