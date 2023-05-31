const { node_windows_x64: nw } = require("../");

console.log(
  nw['user32.messageboxa'](0, "content", "caption", 1)
);
