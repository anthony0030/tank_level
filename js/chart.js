$.getScript('http://cdnjs.cloudflare.com/ajax/libs/raphael/2.1.0/raphael-min.js',function(){
$.getScript('http://cdnjs.cloudflare.com/ajax/libs/morris.js/0.5.0/morris.min.js',function(){

  Morris.Area({
    element: 'area-example',
    data: [
      { day: '01/01', a: 1000},
      { day: '02/01', a: 900},
      { day: '03/01', a: 800},
      { day: '04/01', a: 700},
      { day: '05/01', a: 600},
      { day: '06/01', a: 500},
      { day: '07/01', a: 400},
      { day: '08/01', a: 300},
      { day: '09/01', a: 200},
      { day: '10/01', a: 100},
      { day: '11/01', a: 1000},
      { day: '12/01', a: 900},
      { day: '13/01', a: 800},
      { day: '14/01', a: 700},
      { day: '15/01', a: 600},
      { day: '16/01', a: 500},
      { day: '17/01', a: 400},
      { day: '18/01', a: 300},
      { day: '19/01', a: 200},
      { day: '20/01', a: 100},
      { day: '21/01', a: 0},
      { day: '22/01', a: 1000},
      { day: '23/01', a: 800},
      { day: '24/01', a: 700},
      { day: '25/01', a: 1000},
      { day: '26/01', a: 700},
      { day: '27/01', a: 600},
      { day: '28/01', a: 500},
      { day: '29/01', a: 400},
      { day: '30/01', a: 300},
      { day: '31/01', a: 100}
    ],
        xkey: 'day',
        ykeys: ['a'],
        parseTime: false,
        labels: ['Leiters'],
        pointSize: 2,
        hideHover: 'auto',
        resize: true
  });
  
});
});