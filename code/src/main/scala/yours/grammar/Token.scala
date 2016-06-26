package yours.grammar

abstract class Token
case class TerminalToken(str: String) extends Token
case class SingleWordToken(str: String) extends Token
case class CompoundWordToken(str: String) extends Token
case class CommaToken() extends Token
