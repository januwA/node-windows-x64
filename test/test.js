const nw = require("../build/Release/node-windows-x64");

nw.invoke({
  module: "user32.dll",
  method: "MessageBoxW",
  args: [0, "body", "title", 3],
});