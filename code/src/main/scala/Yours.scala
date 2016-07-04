import yours._

/** Yours command line app.
  *
  * [[file:htmlsrc/Yours.scala.html]]
  */
object Yours extends App {

  Console.println("Yours: " + (args mkString ", "))

  val interpreter = new yours.interpret.Interpreter

  //interpreter("Hello Igor, number 1 super-hero. How are you?")
  interpreter("hello.")

  interpreter.shutdown()
}

