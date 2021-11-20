const cntIns = 10000

const T = 'std::string'
const lists = []
const randint = (max = 1e6) => Math.floor(Math.random() * max)
const pick = arr => arr[randint(arr.length)]
const randomList = () => {
  const keys = [ ...lists.keys() ].filter(x => lists[x])
  return pick(keys)
}
const inss = [
  i => {
    const j = randomList()
    if ([ ...lists.keys() ].filter(x => lists[x]).length > 30) return ';'
    if (!j) {
      lists[i] = []
      return `MyList<${T}> *ll${i} = new MyList<${T}>();`
    }
    return pick([
      () => {
        lists[i] = []
        return `MyList<${T}> *ll${i} = new MyList<${T}>();`
      },
      () => {
        lists[i] = lists[j]
        lists[j] = null
        return `MyList<${T}> *ll${i} = new MyList<${T}>(std::move(*ll${j})); delete ll${j};`
      },
      () => {
        lists[i] = [ ...lists[j] ]
        return `MyList<${T}> *ll${i} = new MyList<${T}>(*ll${j});`
      },
      () => {
        lists[j] = null
        return `delete ll${j};`
      },
    ])()
  },
  () => {
    const j = randomList()
    if (!j) return ';'
    const num = randint()
    lists[j].push(num)
    return `ll${j}->push_back("${num}");`
  },
  () => {
    const j = randomList()
    if (!j) return ';'
    const num = randint()
    lists[j].unshift(num)
    return `ll${j}->push_front("${num}");`
  },
  () => {
    const j = randomList()
    if (!j || !lists[j].length) return ';'
    lists[j].shift();
    return `ll${j}->pop_front();`
  },
  () => {
    const j = randomList()
    if (!j || !lists[j].length) return ';'
    lists[j].pop();
    return `ll${j}->pop_back();`
  },
  () => {
    const j = randomList()
    if (!j) return ';'
    const pos = randint(lists[j].length)
    const num = randint()
    lists[j].splice(pos, 0, num)
    return `ll${j}->insert(${pos}, "${num}");`
  },
  () => {
    const j = randomList()
    if (!j || !lists[j].length) return ';'
    const pos = randint(lists[j].length)
    lists[j].splice(pos, 1)
    return `ll${j}->erase(${pos});`
  },
  () => {
    const j = randomList()
    if (!j) return ';'
    lists[j] = []
    return `ll${j}->clear();`
  },
  () => {
    const j = randomList()
    if (!j || !lists[j].length) return ';'
    return `std::cout << ll${j}->front() << std::endl; /* ${lists[j][0]} */`
  },
  () => {
    const j = randomList()
    if (!j || !lists[j].length) return ';'
    const num = randint()
    lists[j][0] = num
    return `ll${j}->front() = "${num}";`
  },
  () => {
    const j = randomList()
    if (!j || !lists[j].length) return ';'
    const num = randint()
    lists[j][lists[j].length - 1] = num
    return `ll${j}->back() = "${num}";`
  },
  () => {
    const j = randomList()
    if (!j || !lists[j].length) return ';'
    return `std::cout << ll${j}->back() << std::endl;  /* ${lists[j].reduceRight(x => x)} */`
  },
  () => {
    const j = randomList()
    if (!j || !lists[j].length) return ';'
    return `std::cout << ll${j}->size() << std::endl;  /* ${lists[j].length} */`
  },
  () => {
    const j = randomList()
    if (!j || !lists[j].length) return ';'
    return `std::cout << ll${j}->empty() << std::endl;  /* ${lists[j].length === 0 ? 1 : 0} */`
  },
  () => {
    const j = randomList()
    if (!j) return ';'
    return `ll${j}->print(); /* [DEBUG] ${lists[j].join(' ')} */`
  },
  () => {
    const i = randomList()
    const j = randomList()
    if (!i || !j) return ';'
    lists[j].push(...lists[i])
    return `ll${j}->link(*ll${i});`
  },
  i => {
    if ([ ...lists.keys() ].filter(x => lists[x]).length > 3) return ';'
    const j = randomList()
    if (!j || !lists[j].length) return ';'
    const ix = randint(lists[j].length + 1)
    lists[i] = lists[j].slice(ix)
    lists[j] = lists[j].slice(0, ix)
    return `MyList<${T}> *ll${i} = new MyList<${T}>(ll${j}->cut(${ix}));
ll${i}->print(); /* [DEBUG] ${lists[i].join(' ')} */
ll${j}->print(); /* [DEBUG] ${lists[j].join(' ')} */`
  },
  () => {
    const j = randomList()
    if (!j || !lists[j].length) return ';'
    const ix = randint(lists[j].length + 1)
    lists[j] = lists[j].slice(0, ix)
    return `ll${j}->cut(${ix});
ll${j}->print(); /* [DEBUG] ${lists[j].join(' ')} */`
  },
]

console.log(inss[0](1))
for (const i of Array(cntIns).keys()) console.log(pick(inss)(i + 2))

for (const i of lists.keys()) if (lists[i]) console.log(`delete ll${i};`)
