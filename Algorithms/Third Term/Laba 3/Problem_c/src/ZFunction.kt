import java.io.*
import java.util.StringTokenizer


class ZFunction {
    lateinit var reader: FastScanner
    lateinit var writer: PrintWriter


    fun solve() {
        val line = reader.next()
        val zFunctionArray = buildZFunction(line)
        print(zFunctionArray.subList(1, zFunctionArray.size).joinToString(" "))
    }

    fun buildZFunction(line: String): MutableList<Int> {
        val zFunctionArray = MutableList(line.length) { 0 }
        var left = 0
        var right = 0
        for (i in 1 until line.length) {
            zFunctionArray[i] = Math.max(0, Math.min(right - i, zFunctionArray[i - left]))
            while (i + zFunctionArray[i] < line.length && line[zFunctionArray[i]] == line[i + zFunctionArray[i]]) {
                zFunctionArray[i]++
            }
            if (i + zFunctionArray[i] > right) {
                left = i
                right = i + zFunctionArray[i]
            }
        }
        return zFunctionArray
    }

    fun run() {
        reader = FastScanner(File("input" + ".in"))
        writer = PrintWriter(File("output" + ".out"))

        solve()

        writer.close()
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
}

fun main(args: Array<String>) {
    ZFunction().run()
}