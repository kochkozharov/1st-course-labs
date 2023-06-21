#!/usr/bin/env python

OPERATORS = {
    '+': (0, 2, lambda x, y: x + y),
    '-': (0, 2, lambda x, y: x - y),
    '*': (1, 2, lambda x, y: x * y),
    '/': (1, 2, lambda x, y: x / y),
    '%': (1, 2, lambda x, y: x % y)}

class Node:
    def __init__(self, parent, value):
        self.parent, self.value = parent, value

    def __str__(self) -> str:
        result = 'Node('
        if hasattr(self, 'left'):
            result += F'{self.left}, '
        result += str(self.value)
        if hasattr(self, 'right'):
            result += F', {self.right}'
        return result + ')'

    def post_order_next(self):
        if not self.parent:
            return None
        if not hasattr(self.parent, 'right') or self == self.parent.right:
            return self.parent
        node = self.parent.right
        while True:
            if hasattr(node, 'left'):
                node = node.left
            elif hasattr(node, 'right'):
                node = node.right
            else:
                break
        return node

class Tree:
    def __init__(self, root: Node):
        self.root = root

    def __str__(self) -> str:
        return F'Tree({self.root})'

    def calculate(self, context: dict) -> float:
        node, stack = self.post_order_init(), []
        while node:
            value = node.value
            if value in OPERATORS:
                call(value, stack)
            elif isinstance(value, float) or isinstance(value, int):
                stack.append(value)
            else:
                stack.append(context[value])
            node = node.post_order_next()
        assert len(stack) == 1
        return stack[0]

    def post_order_init(self) -> Node:
        node = self.root
        if not node:
            return None
        assert not node.parent
        while True:
            if hasattr(node, 'left'):
                node = node.left
            elif hasattr(node, 'right'):
                node = node.right
            else:
                break
        return node

    def post_order(self, action) -> None:
        node = self.post_order_init()
        while node:
            action(node)
            node = node.post_order_next()

    def to_postfix(self) -> list:
        postfix = []
        self.post_order(lambda node: postfix.append(node.value))
        return postfix

def calculate(postfix: list, context: dict) -> float:
    stack = []
    for token in postfix:
        if token in OPERATORS:
            call(token, stack)
        elif isinstance(token, float) or isinstance(token, int):
            stack.append(token)
        else:
            stack.append(context[token])
    return stack[0]

def call(character: str, stack: list) -> None:
    assert character in OPERATORS
    op, ar = operation(character), arity(character)
    result = op(*stack[-ar:])
    del stack[-ar:]
    stack.append(result)

def priority(character: str) -> int:
    assert character in OPERATORS or character in '()'
    return OPERATORS[character][0] if character in OPERATORS else -1

def arity(character: str) -> int:
    assert character in OPERATORS
    return OPERATORS[character][1]

def operation(character: str) -> int:
    assert character in OPERATORS
    return OPERATORS[character][2]

def infix_to_postfix(expr: str) -> list:
    result = []
    from_infix(expr, result.append)
    return result

def infix_to_tree(expr: str) -> Tree:
    result = []
    from_infix(expr, lambda value: consume_value(value, result))
    return Tree(result.pop() if result else None)

def consume_value(value, result: list) -> None:
    node = Node(None, value)
    if value in OPERATORS:
        if arity(value) >= 2:
            right = result.pop()
            node.right = right
            right.parent = node
        left = result.pop()
        node.left = left
        left.parent = node
    result.append(node)

def from_infix(expr: str, consume) -> None:
    n, i, stack = len(expr), 0, []
    while i < n:
        if expr[i].isspace():
            i += 1
            continue
        if expr[i] == '(':
            stack.append('(')
        elif expr[i] == ')':
            while stack and stack[-1] != '(':
                consume(stack.pop())
            if not stack:
                raise ValueError('incorrect parenthesis')
            stack.pop()
        elif expr[i] in OPERATORS:
            while stack and priority(stack[-1]) >= priority(expr[i]):
                consume(stack.pop())
            stack.append(expr[i])
        elif expr[i].isalpha():
            identifier, i = parse_identifier(expr, i)
            i -= 1
            consume(identifier)
        elif expr[i].isdecimal():
            number, i = parse_number(expr, i)
            i -= 1
            consume(number)
        else:
            raise ValueError(F'incorrect character {expr[i]}')
        i += 1
    stack.reverse()
    for token in stack:
        consume(token)

# карма +1: O(1) по памяти, т.е. без рекурсии и без "стека"
def postfix_to_tree(postfix: list) -> Tree:
    postfix, root, stack = postfix.copy(), None, [(None, False)]
    while stack:
        parent, is_left = stack.pop()
        node = Node(parent, postfix.pop())
        if not parent:
            root = node
        elif is_left:
            parent.left = node
        else:
            parent.right = node
        if node.value in OPERATORS:
            stack.append((node, True))
            if arity(node.value) >= 2:
                stack.append((node, False))
    return Tree(root)

def parse_identifier(expr: str, i: int) -> tuple[str, int]:
    n, token = len(expr), []
    while i < n and expr[i].isalpha():
        token.append(expr[i])
        i += 1
    return ''.join(token), i

def parse_number(expr: str, i: int) -> tuple[float, int]: # strtod in C
    n, dot, token = len(expr), False, []
    while i < n and (expr[i].isdecimal() or expr[i] == '.' and not dot):
        dot = dot or expr[i] == '.'
        token.append(expr[i])
        i += 1
    if not token:
        raise ValueError('incorrect number')
    return (float if dot else int)(''.join(token)), i

assert [2, 3, '+'] == infix_to_postfix('2 + 3')
assert [2, 3, '-'] == infix_to_postfix('2 - 3')
assert [2, 3, '*'] == infix_to_postfix('2 * 3')
assert [2, 3, '/'] == infix_to_postfix('2 / 3')
assert [2, 3, '%'] == infix_to_postfix('2 % 3')

assert [2, 3, '+']       == infix_to_postfix('2.0 + 3.0')
assert [2.25, 3.75, '+'] == infix_to_postfix('2.25 + 3.75')

assert [0, 1, '+', 2, '+', 3, '+'] == infix_to_postfix('0 + 1 + 2 + 3')
assert [1, 2, '*', 3, '*', 4, '*'] == infix_to_postfix('1 * 2 * 3 * 4')

assert [0, 1, '+', 2, 3, '-', '*'] == infix_to_postfix('(0 + 1) * (2 - 3)')
assert [0, 1, 2, '*', '+', 3, '-'] == infix_to_postfix('0 + 1 * 2 - 3')

assert [100, 101, 102, '*', '+', 103, '-'] == infix_to_postfix('100 + (101 * 102) - 103')
assert [100, 101, 102, '*', 103, '%', '+'] == infix_to_postfix('100 + 101 * 102 % 103')
assert [100, 101, 102, '%', 103, '*', '+'] == infix_to_postfix('100 + 101 % 102 * 103')

assert ['ab', 'cd', 'ef', '*', '+', 'gh', '-'] == infix_to_postfix('ab + (cd * ef) - gh')

assert 10503 == calculate([100, 101, 102, '%', 103, '*', '+'], {})
assert 10299 == calculate(
    ['ab', 'cd', 'ef', '*', '+', 'gh', '-'],
    {'ab': 100, 'cd': 101, 'ef': 102, 'gh': 103})

assert parse_number('0', 0)                  == (0, 1)
assert parse_number('.0', 0)                 == (0, 2)
assert parse_number('0.', 0)                 == (0, 2)
assert parse_number('0.0', 0)                == (0, 3)
assert parse_number('1', 0)                  == (1, 1)
assert parse_number('1.0', 0)                == (1, 3)
assert parse_number('1234567890', 0)         == (1234567890, 10)
assert parse_number('123456789.0', 0)        == (123456789, 11)
assert parse_number('1234567890abcdef', 0)   == (1234567890, 10)
assert parse_number('123456789.0abcdef', 0)  == (123456789, 11)
assert parse_number('abcdef 1234567890', 7)  == (1234567890, 17)
assert parse_number('abcdef 123456789.0', 7) == (123456789, 18)
assert parse_number('1234567890 ', 0)        == (1234567890, 10)
assert parse_number('123456789.0 ', 0)       == (123456789, 11)

postfix = [0, 1, '+', 2, 3, '-', '*']
tree = postfix_to_tree(postfix)
assert tree.calculate({}) == -1
assert tree.to_postfix() == postfix
str_tree = 'Tree(Node(Node(Node(0), +, Node(1)), *, Node(Node(2), -, Node(3))))'
assert str(tree) == str_tree
assert str(infix_to_tree('(0 + 1) * (2 - 3)')) == str_tree
print(infix_to_postfix('100 + (101 * 102 - 103'))
# на оценку 4 и 5: возведение в степень (обратите внимание, что оно право-ассоциативное)
# на оценку 5: унарный минус, например
# -5 + 2 * 3
# или
# (2 + 3) * -4
# Карма +1: вариант 99
