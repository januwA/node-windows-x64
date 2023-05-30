const { node_windows_x64: nw } = require("../");

nw['LoadLibraryA']('C:\\Users\\16418\\Desktop\\dll1\\x64\\Release\\dll1.dll');

// int fndll2();
console.log(nw.invoke({
  method: 'dll1.fndll2',
  retType: 'int'
}));

// float fndll3();
console.log(nw.invoke({
  method: 'dll1.fndll3',
  retType: 'float'
}));

// double fndll4();
console.log(nw.invoke({
  method: 'dll1.fndll4',
  retType: 'double'
}));

// INT64 fndll5();
console.log(nw.invoke({
  method: 'dll1.fndll5',
  retType: 'int64'
}));

// short fndll6();
console.log(nw.invoke({
  method: 'dll1.fndll6',
  retType: 'int'
}));