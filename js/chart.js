google.charts.load('current', {'packages':['corechart']});
  google.charts.setOnLoadCallback(drawChart);



  function drawChart() {
    var data = google.visualization.arrayToDataTable([
      ['day', 'Liters'],
      ['01',  1000],
      ['2014',  1170],
      ['2015',  660],
      ['2016',  1030]
    ]);

    var options = {
      title: 'Tank level',
      hAxis: {title: 'Tank Level',  titleTextStyle: {color: '#333'}},
      vAxis: {minValue: 0}
    };

    var chart = new google.visualization.AreaChart(document.getElementById('chart_div'));
    chart.draw(data, options);
  }