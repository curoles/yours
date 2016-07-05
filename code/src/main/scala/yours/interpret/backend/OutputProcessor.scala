/* Copyright Igor Lesik 2016
 *
 * Generates actions and output based on input.
 */
package yours.interpret.backend

import yours.execute.ActionScalaScript

class OutputProcessor {

  /** To call like:
    * {{{
    * outputProcessor(input)
    * }}}
    */
  def apply(input: ParsedText) = process(input)

  /** Thinks and returns action script.
    *
    */
  def process(input: ParsedText): ActionScalaScript = {
    val code = """
      |val greeting = "Hello, world!"
      |println(greeting)
      |""".stripMargin

    new ActionScalaScript(code)
  }
}

