  processor 16c58b

goto_macro macro
       pagesel page0
       goto page0
       pagesel page1
       goto page1
       pagesel page2
       goto page2
       pagesel page3
       goto page3
       endm
  
page0  org 0
       goto_macro

page1  org 201
       goto_macro

page2  org 401
       goto_macro
  
page3  org 601
       goto_macro
 
       end 
