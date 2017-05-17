# pathfinder
Solution optimized for the specific pathfinder case at: https://paradox.kattis.com/problems/paradoxpath
No heuristics used, so it is Dijkstra's algorithm rather than A*
(Huge difference in time consumption when sending the solution to the judge)
Originally vectors were used and checks were in place to verify the ordering of
the Nodes, but since no heuristic is used, this becomes mutch
simpler, and the nodes can be placed in a simple FIFO queue. This also removes
the need to keep track of the path length G when finding the next open node to
close, since they are sorted. However it may still be usefull when keeping track
of the pathlength for the eventual output.
No closed set is needed since the nodes store a boolean determening whether they
are closed or not. So only the currently evaluated closed node needs to be
tracked. Once the target is found, it backtracks through each nodes parent node
to create the entire path.
Trickiest part was realizing that a pathlength of zero was expected if
start==target...
In the end the code is shaved down to fit this specific problem, lacking some
features that might make it more general.
