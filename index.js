const node_windows_x64 = require("bindings")("node-windows-x64");

exports.node_windows_x64 = new Proxy(node_windows_x64, {
  get(target, key) {
    if (key in target) return target[key];
    return function (...args) {
      return target.invoke({
        method: key,
        args: args,
      });
    };
  },
});
