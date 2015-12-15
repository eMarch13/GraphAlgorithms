//
//  WidthFastSearch.cpp
//  GraphsAlgorithms
//
//  Created by Eugene Marchukevich on 11/8/15.
//  Copyright © 2015 Eugene Marchukevich. All rights reserved.
//

#include "WidthFastSearch.hpp"


namespace GraphLibrary
{

    WidthFastSearch :: WidthFastSearch(int _start, int _finish, const BaseGraph &g)
    {
        start = _start;
        finish = _finish;
        graph = (BaseGraph*)&g;
        int n = graph->numberOfVertexes();
        ancestors.resize(n);
        for(int i = 0; i < graph->numberOfVertexes(); i++)
        {
            distance.push_back(MAX_DISTANCE);
        }
    }

    void WidthFastSearch :: search()
    {
        q.push(start);
        distance[start] = 0;
        ancestors[start] = -1;
        while (!q.empty())
        {
            vertex v = q.front();
            q.pop();
            vector<Edge> :: iterator itBegin;
            vector<Edge> :: iterator itEnd;
            vector<Edge> currentEdges;
            if (graph->iteratorBased())
            {
                itBegin = graph->beginForVertex(v);
                itEnd = graph->endForVertex(v);
            } else
            {
                currentEdges = graph->edgesForVertex(v);
                itBegin = currentEdges.begin();
                itEnd = currentEdges.end();
            }
            
            for(vector<Edge> :: iterator it = itBegin; it!=itEnd; it++)
            {
                Edge edge = *it;
                if (distance[edge.finish] > distance[v] + edge.weight)
                {
                    distance[edge.finish] = distance[v] + edge.weight;
                    q.push(edge.finish);
                    ancestors[edge.finish] = v;
                }
            }
        }
    }


    long long WidthFastSearch :: distanceTo(vertex v)
    {
        if (distance[v] == MAX_DISTANCE)
            return -1;
        return distance[v];
    }

    vector<vertex> WidthFastSearch :: wayToVertex(vertex v)
    {
        vector<vertex> way;
        if (distance[v] == MAX_DISTANCE)
            return way;
        
        for (vertex v = finish; v != -1; v = ancestors[v])
            way.push_back(v);
        reverse(way.begin(), way.end());
        return way;
    }

    vector<long long> WidthFastSearch :: allDistances()
    {
        return distance;
    }


    void WidthFastSearch :: setNewData(int _start, int _finish, const BaseGraph &g)
    {
        start = _start;
        finish = _finish;
        graph = (BaseGraph*)&g;
    }

    void WidthFastSearch :: setGraph(const BaseGraph &g)
    {
        graph = (BaseGraph*)&g;
        distance.resize(graph->numberOfVertexes());
        for(int i = 0; i < graph->numberOfVertexes(); i++)
        {
            distance.push_back(MAX_DISTANCE);
        }
        
    }

    void WidthFastSearch :: setStart(vertex s)
    {
        start = s;
    }

    void WidthFastSearch :: setFinish(vertex f)
    {
        finish = f;
    }
}
