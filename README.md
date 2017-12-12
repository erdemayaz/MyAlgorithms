My algorithms repository holds developed algorithm by myself. 

----------


Contents
-------------

#### <i class="icon-file"></i> Popular Path

This algorithm finds most popular paths on directed graphs. It calculates all possible paths in graph and then it calculates paths count nary combination. Finally it gives that path has maximum count as result.<br/>
(Note: A path can include only one time same vertex)

Example;

Assume that a graph has 10 vertex. Adjacency matrix of this graph is:

{<br/>
{0, 0, 0, 0, 1, 1, 0, 0, 0, 1},<br/>
{0, 0, 0, 0, 0, 1, 0, 0, 0, 1},<br/>
{1, 0, 0, 0, 1, 0, 0, 0, 1, 1},<br/>
{0, 1, 0, 0, 1, 0, 1, 0, 0, 1},<br/>
{1, 0, 1, 0, 0, 0, 1, 0, 0, 1},<br/>
{0, 0, 0, 1, 0, 0, 0, 0, 0, 1},<br/>
{0, 0, 0, 1, 0, 1, 0, 0, 1, 1},<br/>
{1, 0, 0, 0, 1, 0, 0, 1, 0, 1},<br/>
{0, 1, 0, 0, 0, 0, 0, 1, 0, 1},<br/>
{0, 0, 0, 0, 1, 1, 0, 0, 0, 1}<br/>
}<br/>

Popular path for 2 togetherness: 6, 4 --> 2940<br/>
Popular path for 3 togetherness: 6, 4, 7 --> 1083<br/>
Popular path for 4 togetherness: 6, 4, 7, 9 --> 578<br/>
Popular path for 5 togetherness: 6, 4, 7, 9, 8 --> 312<br/>
Popular path for 6 togetherness: 10, 6, 4, 7, 9, 8 --> 125<br/>
