let curOp = "";
let recentEvalFlag = false;

const appendDigToScreen = (val) => {
  if (recentEvalFlag) {
    clearScreen();
    recentEvalFlag = false;
  }
  if (document.getElementById("screen").value === "0")
    document.getElementById("screen").value = val.innerText;
  else document.getElementById("screen").value += val.innerText;
};

const appendOpToScreen = (op) => {
  if (document.getElementById("screen").value != "0" && curOp === "") {
    document.getElementById("screen").value += op.innerText;
    curOp = op.innerText;
  }
};

const appendPointToScreen = (op) => {
  if (document.getElementById("screen").value.indexOf(".") != -1) {
    document.getElementById("screen").value += ".";
  }
};

const backspace = () => {
  let s = document.getElementById("screen").value;
  if (s.length === 1) {
    document.getElementById("screen").value = "0";
  } else if (s.length > 0) {
    document.getElementById("screen").value = s.slice(0, s.length - 1);
  }
};

const clearScreen = () => {
  document.getElementById("screen").value = 0;
};

const evaluateExpression = () => {
  let s = document.getElementById("screen").value;
  let operands = null;
  let result = s;
  if (curOp != "") {
    operands = s.split(curOp);
    operands = operands.map((o) => parseFloat(o));
    switch (curOp) {
      case "+":
        result = operands[0] + operands[1];
        break;
      case "-":
        result = operands[0] - operands[1];
        break;
      case "*":
        result = operands[0] * operands[1];
        break;
      case "/":
        result = operands[0] / operands[1];
        break;
      default:
        break;
    }
  }

  if (result === Infinity) {
    alert("Invalid Input!");
    clearScreen();
  } else {
    document.getElementById("screen").value = result.toPrecision(6);
    recentEvalFlag = true;
  }
};
