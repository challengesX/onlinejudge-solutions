const readline = require("readline");

function canNest(boxA, boxB) {
  return boxA.dimensions.every((dim, index) => dim < boxB.dimensions[index]);
}
function findLongestNestingSequence(lines) {
  let i = 0;
  const results = [];

  while (i < lines.length) {
    const [k, n] = lines[i++].split(" ").map(Number);
    const boxes = [];
    for (let j = 0; j < k; j++) {
      const dimensions = lines[i++].split(" ").map(Number);
      boxes.push({
        index: j + 1,
        dimensions: dimensions.slice().sort((a, b) => a - b),
      });
    }
    boxes.sort((a, b) => {
      for (let i = 0; i < a.dimensions.length; i++) {
        if (a.dimensions[i] !== b.dimensions[i]) {
          return a.dimensions[i] - b.dimensions[i];
        }
      }
      return 0;
    });
    const graph = Array(k)
      .fill(0)
      .map(() => []);
    for (let u = 0; u < k; u++) {
      for (let v = u + 1; v < k; v++) {
        if (canNest(boxes[u], boxes[v])) {
          graph[u].push(v);
        }
      }
    }
    const dp = Array(k).fill(1);
    const prev = Array(k).fill(-1);
    for (let u = 0; u < k; u++) {
      for (const v of graph[u]) {
        if (dp[u] + 1 > dp[v]) {
          dp[v] = dp[u] + 1;
          prev[v] = u;
        } else if (dp[u] + 1 === dp[v] && u < prev[v]) {
          prev[v] = u;
        }
      }
    }
    let maxLength = 0;
    let maxIndex = -1;
    for (let u = 1; u < k; u++) {
      if (dp[u] >= maxLength) {
        maxLength = dp[u];
        maxIndex = u;
      }
    }
    const sequence = [];
    while (maxIndex !== -1) {
      sequence.push(boxes[maxIndex].index);
      maxIndex = prev[maxIndex];
    }

    results.push(`${maxLength}`);
    results.push(sequence.reverse().join(" "));
  }

  return results.join("\n");
}

const main = async () => {
  const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  const lines = [];
  console.log("Enter input (end with an empty line):");
  for await (const line of rl) {
    if (line.trim() === "") break;
    lines.push(line.trim());
  }
  const output = findLongestNestingSequence(lines);
  console.log(output);
  rl.close();
};
main();
