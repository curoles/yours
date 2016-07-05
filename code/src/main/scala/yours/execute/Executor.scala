/* Copyright Igor Lesik 2016
 *
 * Executes commands/tasks/actions.
 */
package yours.execute

import akka.actor.Actor
import akka.actor.Props

import scala.reflect.runtime._
import scala.tools.reflect.ToolBox

/** Helps class Executor */
object Executor {

  /** Creates properties for the Actor.
    *
    */
  val props = Props[Executor]
  //def props : Props = Props(new Executor)

  /*
   * Create Props for an actor of this type.
   *
   * @param magicNumber The magic number to be passed to this actor’s constructor.
   * @return a Props for creating this actor, which can then be further configured
   *         (e.g. calling `.withDispatcher()` on it)
   *
  def props(magicNumber: Int): Props = Props(new DemoActor(magicNumber))
   */
  /*case class Greeting(from: String)
  case object Goodbye
to use
    case Greeting(greeter) => log.info(s"I was greeted by $greeter.")
    case Goodbye           => log.info(
   */
}

class Executor extends Actor {

  def receive = {
    case s : ActionScalaScript => evalScalaScript(s)
    case _ => println("executor got unknown message")
  }

  def evalScalaScript(actionScript:ActionScalaScript) {
    println(actionScript.scalaCode)
    val code = actionScript.scalaCode.stripMargin
    val cm = universe.runtimeMirror(getClass.getClassLoader)
    val tb = cm.mkToolBox()

    tb.eval(tb.parse(code))
    sender ! "Done."
  }
}

