import yours.grammar._

/** Yours command line app.
 *
 */
object Yours extends App {
  //println("Hello, world!")
  Console.println("Yours: " + (args mkString ", "))

  val parser = new SentenceParser
  val result = parser.parseAll(parser.sentence, "Hello Igor, number 1 super-hero.")
  println("result:" + result)
  if (result.successful) println(result.get)
}

