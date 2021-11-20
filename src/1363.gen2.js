const cntIns = 10000

const T = 'std::string'
const list = []
const randint = (max = 1e6) => Math.floor(Math.random() * max)
const pick = arr => arr[randint(arr.length)]
const inss = [
  () => {
    const num = randint()
    list.push(num)
    return `ll.push_back("${num}");`
  },
  () => {
    const num = randint()
    list.unshift(num)
    return `ll.push_front("${num}");`
  },
  () => {
    if (!list.length) return ';'
    list.shift()
    return `ll.pop_front();`
  },
  () => {
    if (!list.length) return ';'
    list.pop()
    return `ll.pop_back();`
  },
  () => {
    const pos = randint(list.length)
    const num = randint()
    list.splice(pos, 0, num)
    return `ll.insert(${pos}, "${num}");`
  },
  () => {
    if (!list.length) return ';'
    const pos = randint(list.length)
    list.splice(pos, 1)
    return `ll.erase(${pos});`
  },
  () => {
    list.length = 0
    return `ll.clear();`
  },
  () => list.length === 0 ? ';' : `std::cout << ll.front() << std::endl; /* ${list[0]} */`,
  () => list.length === 0 ? ';' : `std::cout << ll.back() << std::endl;  /* ${list.reduceRight(x => x)} */`,
  () => `std::cout << ll.size() << std::endl;  /* ${list.length} */`,
  () => `std::cout << ll.empty() << std::endl;  /* ${list.length === 0 ? 1 : 0} */`,
  () => `ll.print(); /* [DEBUG] ${list.join(' ')} */`,
  () => {
    list.push('a', 'b')
    return `ll.link(ll1);`
  },
  () => {
    list.push(...list)
    return `ll.link(ll);`
  },
  () => {
    const ix = randint(list.length + 1)
    list.length = ix
    return `ll.cut(${ix});`
  },
]

console.log(`MyList<${T}> ll;`)
for (const i of Array(cntIns).keys()) console.log(pick(inss)(i))
