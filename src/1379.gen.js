let length = 1000
const rand = x => Math.floor(Math.random() * x)
const randnum = () => rand(1e5)
const randi = () => rand(length)
console.log(length)
console.log(Array(length).fill(0).map(() => randnum()))
const numOps = 10000
console.log(numOps)
for (const _ of Array(numOps).keys()) {
  const op = Math.floor(Math.random() * 7)
  switch (op) {
    case 0:
      length++
      console.log(0, Math.floor(Math.random() * length), randnum())
      break
    case 1:
      length--
      console.log(1, randi())
      break
    case 2:
      console.log(2)
      break
    case 3:
      length = randi()
      console.log(3, length)
      break
    case 4:
      console.log(4, randi())
      break
    case 5:
      console.log(5)
      break
    case 6:
      console.log(6)
      break
  }
}
