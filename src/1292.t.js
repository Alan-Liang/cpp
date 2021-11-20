const kYears = 9999
const kMonthsInYear = 12

const presum = (prev, curr) => [ ...prev, prev[prev.length - 1] + curr ]
const isLeap = year => year % 100 === 0 ? year % 400 === 0 : year % 4 === 0
const daysInYear = Array.from(Array(kYears - 1).keys()).map(year => year + 1).map(isLeap).map(leap => leap ? 366 : 365)
const yearOffset = daysInYear

const kDaysInMonth = [ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 ]
const kDaysInMonthLeap = kDaysInMonth.map((d, m) => m == 1 ? d + 1 : d)

console.log(`
constexpr int kYears = ${kYears};
constexpr int kMonthsInYear = ${kMonthsInYear};
constexpr int kDaysInMonth[kMonthsInYear] = {${kDaysInMonth.join(',')}};
constexpr int kDaysInMonthLeap[kMonthsInYear] = {${kDaysInMonthLeap.join(',')}};
constexpr int kMonthOffset[kMonthsInYear] = {${kDaysInMonth.slice(0, -1).reduce(presum, [ 0 ]).join(',')}};
constexpr int kMonthOffsetLeap[kMonthsInYear] = {${kDaysInMonthLeap.slice(0, -1).reduce(presum, [ 0 ]).join(',')}};
constexpr int kYearOffset[kYears] = {${daysInYear.reduce(presum, [ 0 ]).join(',')}};
`.trim())
