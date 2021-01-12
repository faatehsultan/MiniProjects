//loading bar generator (developed by github.com/faatehsultan)

const startLoadingBar = async (duration = 10, headingText = "L o a d i n g . . .") => {
  let content = {
    "html": '<heading class="text-shadow-shift">' + headingText + '</heading><div class="loading-border"><div id="loading1">0</div><div class="width-shift"><div class="rainbow-loading color-shift"></div></div></div>',
    "css": ":root { height: 100%; --color1: #0984e3; --color2: #6c5ce7; --color3: #e84393; --color4: #d63031; --color5: #00b894; }.rainbow-loading-container {display: flex;align-items: center;justify-content: center;flex-direction: column;}.rainbow-loading {height: 80px;display: flex;align-items: center;justify-content: center;border-radius: 10px;}heading {color: white;text-align: center;text-transform: uppercase;font-family: 'Verdana';font-weight: bold;font-size: 2.2em;margin-bottom: 30px;}.loading-border {width: 450px;height: 80px;border: 9px solid white;border-radius: 20px;}    .width-shift {     animation-name: loading-width-shifter;     animation-duration:" +  duration + "s;     animation-timing-function: linear;   }    @keyframes loading-width-shifter {0% {width: 0%;}100% {width: 100%;}}.color-shift {     animation-name: theme-color-shifter;     animation-duration: 4s;     animation-iteration-count: infinite;     animation-direction: alternate-reverse;   }    @keyframes theme-color-shifter {     0% {       background-color: var(--color1);     }      25% {       background-color: var(--color2);     }      50% {       background-color: var(--color3);     }      75% {       background-color: var(--color4);     }      100% {       background-color: var(--color5);     }   }    .text-shadow-shift {     animation-name: text-shadow-shifter;     animation-duration: 4s;     animation-iteration-count: infinite;     animation-direction: alternate-reverse;   }    @keyframes text-shadow-shifter {     0% {       text-shadow: 0px 0px 20px var(--color1);     }      25% {       text-shadow: 0px 0px 20px var(--color2);     }      50% {       text-shadow: 0px 0px 20px var(--color3);     }      75% {       text-shadow: 0px 0px 20px var(--color4);     }      100% {       text-shadow: 0px 0px 20px var(--color5);     }   }    #loading1 {     color: white;     text-align: center;     text-transform: uppercase;     font-family: 'Verdana';     font-weight: bold;     font-size: 1.8em;     text-shadow: 0px 0px 15px black;     margin-bottom: -55px;     margin-top: 20px;   }"
  };

  let i = 0;
  let inter = setInterval(async () => {
    document.querySelector('#loading1').textContent = i++;
    if (i == 101) clearInterval(inter);
  }, duration*10);

  document.querySelector("style").textContent += content.css;
  document.querySelector(".rainbow-loading-container").innerHTML = content.html;
}

//available on CDN 