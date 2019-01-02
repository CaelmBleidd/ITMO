import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.*

class ProblemA {

    val br = BufferedReader(InputStreamReader(System.`in`))
    var st: StringTokenizer? = null


    fun run() {
        solve()
    }

    fun solve() {


        val n = nextInt()
        val m = nextInt()

        val edges = mutableListOf<Edge>()
        val edgeByVertex = MutableList<MutableList<Int>>(n + 1) {
            mutableListOf()
        }

        val hamiltonianCycle = mutableListOf<Int>()

        edgeByVertex.map { mutableListOf<Int>() }

        for (i in 1..m) {
            val first = nextInt()
            val second = nextInt()
            edges.add(Edge(Math.min(first, second), Math.max(second, first)))
            edgeByVertex[first].add(second)
            edgeByVertex[second].add(first)

        }

        for (i in 1..n) {
            hamiltonianCycle.add(nextInt())
        }

        val edgesInNewGraph = makeNewGraph(m, edges, edgeByVertex, hamiltonianCycle)
        val used = MutableList(m + 1) { false }
        val part = MutableList(m + 1) { -1 }

        for (i in 1..m) {
            if (!used[i]) {
                isBipartite(i, 1, edgesInNewGraph, used, part)
            }
        }

        if (part[0] != -1)
            print("NO")
        else {
            println("YES")
            val cycleToLine = mutableMapOf<Int, Int>()
            val line = makeLine(n, cycle = hamiltonianCycle, image = cycleToLine)
            for (i in 1..n) {
                print("${line[cycleToLine[i]!!].x} ${line[cycleToLine[i]!!].y} ".format(Locale.US))
            }
            println()
            draw_edges(edges, part, cycleToLine, line)
        }
    }


    fun makeLine(n: Int, cycle: MutableList<Int>, image: MutableMap<Int, Int>): MutableList<Point> {
        val line = mutableListOf<Point>()
        for (i in 0 until n) {
            line.add(Point(i.toDouble(), 0.0))
            image[cycle[i]] = i
        }
        return line
    }

    fun draw_edges(edges: MutableList<Edge>, part: MutableList<Int>, image: MutableMap<Int, Int>, line: MutableList<Point>) {
        val answer = mutableListOf<Point>()
        for (edgeIndex in edges.indices) {
            val x = line[image[edges[edgeIndex].start]!!]
            val y = line[image[edges[edgeIndex].end]!!]
            if (part[edgeIndex + 1] == 0) { // внешние (?)
                answer.add(getCenter(x, y))
            } else { // внутренние
                answer.add(invert(getCenter(x, y)))

            }
        }
        answer.forEach {
            println("${it.x} ${it.y}".format(Locale.US))
        }
    }


    fun getCenter(first: Point, second: Point): Point {
        val radius = (Math.max(first.x, second.x) - Math.min(first.x, second.x)) / 2
        return Point(x = (first.x + second.x) / 2, y = radius)
    }


    fun invert(point: Point) : Point {
        return Point(x = point.x, y = -point.y)
    }


    fun makeNewGraph(
        m: Int,
        edges: MutableList<Edge>,
        edgesByVertex: MutableList<MutableList<Int>>,
        cycle: MutableList<Int>
    ): MutableList<MutableList<Int>> {

        val newEdges = MutableList<MutableList<Int>>(m + 1) {
            mutableListOf()
        }

        for (edge in edges) {
            val start = edge.start
            val end = edge.end


            val startPosition = Math.min(cycle.indexOf(start), cycle.indexOf(end))
            val endPosition =  Math.max(cycle.indexOf(start), cycle.indexOf(end))

            for (number in startPosition + 1 until endPosition) {
                val vertex = cycle[number]
                for (endEdge in edgesByVertex[vertex]) {
                    if (cycle.indexOf(endEdge) < startPosition || cycle.indexOf(endEdge) > endPosition) {
                        if (edges.contains(Edge(vertex, endEdge)))
                            newEdges[edges.indexOf(edge) + 1].add(edges.indexOf(Edge(vertex, endEdge)) + 1)
                        else
                            newEdges[edges.indexOf(edge) + 1].add(edges.indexOf(Edge(endEdge, vertex)) + 1)
                    }
                }
            }
        }
        return newEdges
    }

    fun isBipartite(
        vertex: Int,
        lastColor: Int,
        graph: MutableList<MutableList<Int>>,
        used: MutableList<Boolean>,
        part: MutableList<Int>
    ) {

        if (part[0] != -1 || used[vertex]) return

        used[vertex] = true

        when (lastColor) {
            0 -> part[vertex] = 1
            1 -> part[vertex] = 0
            else -> part[vertex] = 0
        }

        for (i in graph[vertex]) {
            if (!used[i])
                isBipartite(i, part[vertex], graph, used, part)
            else {
                if (part[i] == part[vertex] && part[i] != -1)
                    part[0] = 10000
            }
        }

    }

    fun next(): String {
        while (st == null || !st!!.hasMoreTokens()) {
            st = StringTokenizer(br.readLine())
        }
        return st!!.nextToken()
    }

    fun nextInt(): Int {
        return next().toInt()
    }

    data class Edge(val start: Int, var end: Int)

    data class Point(val x: Double, val y: Double)


}

fun main(args: Array<String>) {
    ProblemA().run()
}