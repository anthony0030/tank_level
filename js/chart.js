$.getScript('http://cdnjs.cloudflare.com/ajax/libs/raphael/2.1.0/raphael-min.js',function(){
$.getScript('http://cdnjs.cloudflare.com/ajax/libs/morris.js/0.5.0/morris.min.js',function(){

  Morris.Area({
    element: 'area-example',
    data: [
      { y: '1.1.', a: 100, b: 90 },
      { y: '2.1.', a: 75,  b: 65 },
      { y: '3.1.', a: 50,  b: 40 },
      { y: '4.1.', a: 75,  b: 65 },
      { y: '5.1.', a: 50,  b: 40 },
      { y: '6.1.', a: 75,  b: 65 },
      { y: '7.1.', a: 100, b: 90 }
    ],
    xkey: 'y',
    ykeys: ['a', 'b'],
    labels: ['Series A', 'Series B']
  });
  
});
});