const nw = require("../build/Release/node-windows-x64");

nw.invoke({
  method: "user32.MessageBoxA",
  args: [0, "body", "title", 3],
  isWideChar: false,
});
