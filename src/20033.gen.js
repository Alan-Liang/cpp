const n = 1e5
const q = 1e6
const randint = max => Math.floor(Math.random() * max)

class Node {
  id = 0
  parent = 0
  weight = 0
  depth = 0
  children = []
  attach (child) {
    child.parent = this
    child.depth = this.depth + 1
    this.children.push(child)
  }
}

const root = new Node()
const nodes = [ root ]

console.log(`${n} ${n - 1}`)
for (const i of Array(n - 1).keys()) {
  const node = new Node()
  node.id = i + 1
  node.weight = randint(1e3)
  const p = randint(i + 1)
  nodes[p].attach(node)
  console.log(`${node.id + 1} ${node.parent.id + 1} ${node.weight}`)
  nodes.push(node)
}

const get = (x, y) => {
  if (x.depth > y.depth) [ x, y ] = [ y, x ]
  let p = 0
  while (y.depth > x.depth) {
    p += y.weight
    y = y.parent
  }
  while (x.id != y.id) {
    p += x.weight
    p += y.weight
    x = x.parent
    y = y.parent
  }
  return p
}

console.log(q)
for (const _ of Array(q).keys()) {
  const x = randint(n)
  const y = randint(n)
  console.log(`${x + 1} ${y + 1}`)
  console.error(get(nodes[x], nodes[y]))
}
