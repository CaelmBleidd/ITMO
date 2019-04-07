import java.io.*
import java.lang.Integer.min
import java.lang.Math.abs
import java.util.*
import kotlin.math.hypot
import kotlin.math.sqrt


class Dinic {
    lateinit var reader: FastScanner

    val MAX_V = 100 + 5
    val INF = 1_000_000_000
    val EPS = 0.00001

    var shortestPaths = IntArray(MAX_V) { -1 }
    var deletedV = IntArray(MAX_V) { 0 }

    var tubes = Array<ArrayList<Int>>(MAX_V) { ArrayList() }

    var edges = mutableListOf<Edge>()

    var n = 0
    var maxFlow = 0
    var s = 1
    var t = 1

    var items = mutableListOf<Item>()
    var positions = mutableListOf<Position>()


    fun addEdge(from: Int, to: Int, capacity: Int, isReversed: Boolean) {
        val firstEdge = Edge(from, to, capacity, 0, isReversed)
        val secondEdge = Edge(to, from, 0, 0, !isReversed)

        tubes[from].add(edges.size)
        edges.add(firstEdge)

        tubes[to].add(edges.size)
        edges.add(secondEdge)
    }

    fun input() {
        reader = FastScanner(File("input" + ".in"))
        n = reader.nextInt()
        for (i in 0 until n) {
            items.add(Item(Position(reader.nextInt(), reader.nextInt()), reader.nextInt()))
        }
        for (i in 0 until n) {
            positions.add(Position(reader.nextInt(), reader.nextInt()))
        }
    }


    fun getTime(item: Item, position: Position): Double {
        return getDistance(item, position) / item.speed
    }

    fun getDistance(item: Item, position: Position): Double {
        return hypot(item.position.x.toDouble() - position.x, item.position.y.toDouble() - position.y)
    }

    fun reset() {
        tubes.forEach { it.clear() }
        edges.clear()
        maxFlow = 0
    }

    fun exists(time: Double): Boolean {
        reset()

        for (i in items.withIndex()) {
            for (j in positions.withIndex()) {
                if (getTime(i.value, j.value) <= time) {
                    addEdge(i.index + 1, j.index + 1 + n, 1, false)
                }
            }
        }

        s = 0
        t = n + n + 1

        for (i in items.indices) {
            addEdge(s, i + 1, 1, false)
            addEdge(n + i + 1, t, 1, false)
        }



        findMaxFlow()

        if (maxFlow != n)
            return false
        return true
    }

    fun binaryTimeSearch(): Double {
        var left = 0.0
        var right = Double.MAX_VALUE
        while (right - left > EPS) {
            val middle = (left + right) / 2
            if (exists(middle))
                right = middle
            else
                left = middle

        }
        return left
    }

    fun findMaxFlow(): Int {
        while (true) {
            if (!findShortestPaths()) break

            deletedV.fill(0)
            while (true) {
                val pushedFlow = pushFlow(s, INF)
                maxFlow += pushedFlow
                if (pushedFlow == 0)
                    break
            }
        }
        return maxFlow
    }

    fun findShortestPaths(): Boolean {
        shortestPaths.fill(-1)
        val bfsQueue = ArrayDeque<Int>()
        bfsQueue.add(s)
        shortestPaths[s] = 0

        while (bfsQueue.isNotEmpty()) {
            val v = bfsQueue.poll()
            for (toEdgeNumber in tubes[v]) {
                val edge = edges[toEdgeNumber]

                if (shortestPaths[edge.to] == -1 && edge.flow < edge.capacity) {
                    shortestPaths[edge.to] = shortestPaths[v] + 1
                    bfsQueue.add(edge.to)
                }
            }
        }
        return shortestPaths[t] != -1
    }

    fun pushFlow(v: Int, flow: Int): Int {
        if (flow == 0) return 0
        if (v == t) return flow

        for (to in deletedV[v] until tubes[v].size) {
            val id = tubes[v][deletedV[v]]
            val toEdge = edges[id].to

            if (shortestPaths[toEdge] != shortestPaths[v] + 1) {
                deletedV[v]++
                continue
            }
            val pushed = pushFlow(toEdge, min(flow, edges[id].capacity - edges[id].flow))
            if (pushed > 0) {
                edges[id].flow += pushed
                edges[id xor 1].flow -= pushed
                return pushed
            }

            deletedV[v]++
        }
        return 0
    }

    fun measureTime(executing: String, f: () -> Unit) {
        val start = System.nanoTime()
        f()
        println(executing + ": run for ${(System.nanoTime() - start) / 10e9}")
    }


    inner class FastScanner(file: File) {
        var br: BufferedReader = BufferedReader(InputStreamReader(System.`in`))
        var st: StringTokenizer? = null

        fun next(): String {
            while (st == null || !st!!.hasMoreTokens()) {
                st = StringTokenizer(br.readLine())
            }
            return st!!.nextToken()
        }

        fun nextInt(): Int {
            return next().toInt()
        }

        fun nextLong(): Long {
            return next().toLong()
        }

        fun nextDouble(): Double {
            return next().toDouble()
        }
    }

    data class Edge(val from: Int, val to: Int, val capacity: Int, var flow: Int, val isReversed: Boolean)
    data class Position(var x: Int, var y: Int)
    data class Item(var position: Position, val speed: Int)
}


fun main() {
    val dinic = Dinic()
    dinic.input()
    print(String.format("%.5f", dinic.binaryTimeSearch()))
}