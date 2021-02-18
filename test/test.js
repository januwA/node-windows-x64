const nw = require("../build/Release/node-windows-x64");
const assert = require("assert");
// console.log(addon);

r = nw.invoke({
  module: "user32.dll",
  method: "MessageBoxW",
  args: [0, "body", "title", 3],
});

console.log(r);
