import yours._

/** Yours command line app.
 *
 */
object Yours extends App {

  Console.println("Yours: " + (args mkString ", "))

  val inputProcessor = new InputProcessor

  inputProcessor("Hello Igor, number 1 super-hero.")
}

