const { createInterface } = require("readline/promises");
const { stdin: input, stdout: output } = require("node:process");
function cycleLength(n) {
  var l = 1;
  while (n !== 1) {
    if (n % 2 !== 0) {
      n = 3 * n + 1;
    } else {
      n = n / 2;
    }
    l++;
  }
  return l;
}
function maxCycleLength(i, j) {
  var max = 0;
  for (let k = Math.min(i, j); k <= Math.max(i, j); k++) {
    max = Math.max(max, cycleLength(k));
  }
  return max;
}
(async () => {
  const interface = createInterface({ input, output });
  while (true) {
    const input = await interface.question("Enter i and j or e for exit: ");
    if (input.toLocaleLowerCase() === "e") break;
    const [i, j] = input.split(" ").map(Number);
    const maxLength = maxCycleLength(i, j);
    console.log(`${i} ${j} ${maxLength}`);
  }
  interface.close();
})();
