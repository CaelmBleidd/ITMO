import java.io.*
import kotlin.math.max
import kotlin.math.min


class FastScanner(file: File) {
    var st = StreamTokenizer(System.`in`.bufferedReader())

    fun nextInt(): Long {
        st.nextToken()
        return st.nval.toLong()
    }
}


fun main() {
    val reader = FastScanner(File("input.in" + ".in"))

    val n = reader.nextInt().toInt()
    val w = reader.nextInt().toInt()

    val INF = Long.MAX_VALUE / 1000L

    val was = Array(n + 2) { false }
    val distances = Array(n + 2) { INF }
    val vertex = Array(n + 2) { Array(n + 2) { 0L } }

    val x1 = LongArray(n) { 0L }
    val x2 = LongArray(n) { 0L }
    val y1 = LongArray(n) { 0L }
    val y2 = LongArray(n) { 0L }

    for (i in 0 until n) {
        x1[i] = (reader.nextInt())
        y1[i] = (reader.nextInt())
        x2[i] = (reader.nextInt())
        y2[i] = (reader.nextInt())
    }

    vertex[0][n + 1] = w.toLong()
    vertex[n + 1][0] = w.toLong()

    for (curRec in 0 until n) {
        val minY = min(y1[curRec], y2[curRec])
        val maxY = max(y1[curRec], y2[curRec])
        val wMaxY = w - maxY
        vertex[0][curRec + 1] = wMaxY
        vertex[curRec + 1][0] = wMaxY
        vertex[n + 1][curRec + 1] = minY
        vertex[curRec + 1][n + 1] = minY

        for (j in 0 until n) {
            if (curRec != j) {
                val hor = if (x1[curRec] <= x1[j]) x1[j] - x2[curRec] else x1[curRec] - x2[j]
                val ver = if (y1[curRec] <= y1[j]) y1[j] - y2[curRec] else y1[curRec] - y2[j]
                vertex[curRec + 1][j + 1] = max(0, max(ver, hor))
                vertex[j + 1][curRec + 1] = max(0, max(ver, hor))
            }
        }
    }

    distances[0] = 0L
    for (i in 0 until n + 2) {
        var v = -1
        for (j in 0 until n + 2) {
            if (!was[j] && (v == -1 || distances[j] < distances[v]))
                v = j
        }
        if (distances[v] == INF)
            break
        was[v] = true
        for (u in 0 until n + 2) {
            if (v != u) {
                val d = vertex[v][u]
                if (distances[v] + d < distances[u])
                    distances[u] = distances[v] + d
            }
        }
    }
    print(if (distances[n + 1] == INF) 0 else distances[n + 1])

}