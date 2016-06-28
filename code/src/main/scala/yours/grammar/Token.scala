package yours.grammar

abstract class Token
case class TerminalToken(str: String) extends Token
case class SingleWordToken(str: String) extends Token
case class CompoundWordToken(str: String) extends Token
case class NumberToken(str: String) extends Token
case class CommaToken() extends Token
case class SentenceToken(words:List[Token], terminal:TerminalToken) extends Token
