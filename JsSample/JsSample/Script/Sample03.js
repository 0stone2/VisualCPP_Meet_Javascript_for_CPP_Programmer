/*
JavaScript (Sample03.js)코드입니다.
*/

szWelcomMessage = "Hello World";
szWhoamI = "Sample03.js";

function myfunc_1 () {
	szWhoamI = "myfunc_1";
}

function myfunc_2 () {
	szWhoamI= "myfunc_2";
	return szWhoamI;
}

function myfunc_3 (szNewMyName) {
	szWhoamI= szNewMyName;
	return ["Success", true];
}

function myfunc_4 (szNewMyName, bReturnValue) {
	szWhoamI = szNewMyName;
	return ["Success", bReturnValue];
}