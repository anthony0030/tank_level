function map_range(value, low1, high1, low2, high2) {
    return low1 + (high1 - low1) * (value - low2) / (high2 - low2);
}

var temp_value = 30;
var hum_value = 50;
var tank_value = 750;

var temp_line = " p"+ map_range(temp_value, 0, 100, 0, 40);
var hum_line = " p"+ hum_value;
var tank_line = " p"+ map_range(tank_value, 0, 100, 0, 1000);



document.getElementById('tank_print').innerHTML=tank_value+"&nbsp;L";
document.getElementById('hum_print').innerHTML=hum_value+"&nbsp;%";
document.getElementById('temp_print').innerHTML=temp_value+"&nbsp;&#176;C";

document.getElementById('tank_line').className += tank_line;
document.getElementById('hum_line').className += hum_line;
document.getElementById('temp_line').className += temp_line;