/* wrong */
for(var i = 1; i < 10; i++) {  
     setTimeout(function() { alert(i) }, 100);
}


/* correct */
for(var i = 1; i < 10; i++) { 
    (function(index) { 
       setTimeout(function() { 
        alert(index); }, 100);})(i); 
}