module ImpParser where

import Parsing
import ImpSyntax
import System.Environment
import Control.Monad
import Control.Applicative ((<*>))

-- programs
prog :: Parser Prog
prog = do
      fs <- many fundefn
      ss <- many stmt
      return (fs, ss)

-- function definitions
fundefn :: Parser FunDefn
fundefn = do
      symbol "function"
      n  <- identifier
      ns <- parens (identifier `sepBy` comma)
      ss <- braces (many stmt)
      return (n, ns, ss)

-- statements
stmt :: Parser Stmt
stmt = (do
            i <- identifier
            symbol ":="
            e <- expr
            symbol ";"
            return (Assign i e))
      +++ (do
            symbol "return"
            e <- expr
            symbol ";"
            return (Return e))
      +++ (do
            symbol "let"
            i <- identifier
            symbol ":="
            e <- expr
            symbol "in"
            ss_t <- braces (many stmt)
            return (Let i e ss_t))
      +++ (do
            symbol "for"
            (stmt1, be, stmt2) <- parens (do
                  stmt1 <- (do
                        i <- identifier
                        symbol ":="
                        e <- expr
                        symbol ";"
                        return (Assign i e))
                  be <- bexpr
                  symbol ";"
                  stmt2 <- (do
                        i <- identifier
                        symbol ":="
                        e <- expr
                        return (Assign i e))
                  return (stmt1, be, stmt2))
            ss <- braces (many stmt)
            return $ For stmt1 be stmt2 ss)
      +++ (do
            symbol "case"
            e    <- expr
            arms <- braces (many caseArm)
            return (Case e arms))
      +++ (do
            symbol "if"
            be    <- bexpr
            ss_t  <- braces (many stmt)
            melse <- optionMaybe (symbol "else")
            case melse of
                  Nothing -> return (If be ss_t [])
                  Just _ -> do
                        ss_f <- braces (many stmt)
                        return (If be ss_t ss_f))
      +++ (do
            symbol "while"
            be   <- bexpr
            ss_t <- braces (many stmt)
            return (While be ss_t))

caseArm :: Parser (Int, [Stmt])
caseArm = do
      n  <- integer
      ss <- braces (many stmt)
      return (n, ss)

infixOp :: Parser (t -> t -> a) -> Parser t -> Parser a
infixOp op t = do
      e1 <- t
      cons <- op
      e2 <- t
      return $ cons e1 e2

prefixOp :: Parser (t -> a) -> Parser t -> Parser a
prefixOp op t = do
      cons <- op
      e <- t
      return $ cons e

-- operator table
opTable = map prefixOp
      [ (symbol "-" >> return Neg)
      ] ++ map infixOp
      [ (symbol "*" >> return Mul)
      , (symbol "+" >> return Add)
      , (symbol "-" >> return Sub)
      ]

-- terms
term :: Parser Exp
term = parens expr
      +++ liftM LitInt integer
      +++ (do
            i     <- identifier
            margs <- optionMaybe (parens (expr `sepBy` comma))
            case margs of
                  Nothing   -> return (Var i)
                  Just args -> return (FunCall i args))

-- expressions
expr :: Parser Exp
expr = buildExprParser opTable term
      +++ term

-- operator table for bexps
bopTable = map prefixOp
      [ (symbol "!" >> return Not)
      ] ++ map infixOp
      [ (symbol "&&" >> return And)
      , (symbol "||" >> return Or)
      ]

-- comparison operators for bexps
compOpTable = map infixOp
      [ (symbol ">" >> return IsGT)
      , (symbol "<" >> return IsLT)
      , (symbol ">=" >> return IsGTE)
      , (symbol "<=" >> return IsLTE)
      , (symbol "==" >> return IsEq)
      , (symbol "!=" >> return IsNEq)
      ]

-- terms for bexps
bterm :: Parser BExp
bterm = parens bexpr
      +++ (symbol "true" >> return (LitBool True))
      +++ (symbol "false" >> return (LitBool False))

bexpr :: Parser BExp
bexpr = buildExprParser bopTable bterm
      +++ buildExprParser compOpTable term
      +++ bterm

buildExprParser ops t = foldr (+++) failure (ops <*> [t])

-- utility function to expand ~ in filenames
expandFilePath :: FilePath -> IO FilePath
expandFilePath ('~':'/':s) = do
      hd <- getEnv "HOME"
      return (hd ++ "/" ++ s)
expandFilePath s = return s

-- main entry points for parser
parseImp :: FilePath -> IO Prog
parseImp p_ = do
      p <- expandFilePath p_
      s <- readFile p
      let pr =  parse (space >> prog >>= \ pg -> space >> return pg) s
      case pr of
            [(prog, _)] -> return prog
            _ -> error "Parsing failed."

parseFile :: FilePath -> IO Prog
parseFile = parseImp

parseProg :: String -> Prog
parseProg s = case parse (space >> prog >>= \ pg -> space >> return pg) s of
      [(prog, _)] -> prog
      _ -> error "Parsing failed."

parseStmt :: String -> Stmt
parseStmt s = case parse (space >> stmt >>= \ st -> space >> return st) s of
      [(prog, _)] -> prog
      _ -> error "Parsing failed."

parseExp :: String -> Exp
parseExp s = case parse (space >> expr >>= \ e -> space >> return e) s of
      [(prog, _)] -> prog
      _ -> error "Parsing failed."

parseExps :: String -> [Exp]
parseExps s = case parse (space >> (expr `sepBy` comma) >>= \ e -> space >> return e) s of
      [(prog, _)] -> prog
      _ -> error "Parsing failed."


parseBExp :: String -> BExp
parseBExp s = case parse (space >> bexpr >>= \ e -> space >> return e) s of
      [(prog, _)] -> prog
      _ -> error "Parsing failed."

-- Extra stuff like parsec does it.

parens :: Parser a -> Parser a
parens p = do
      symbol "("
      v <- p
      symbol ")"
      return v

braces :: Parser a -> Parser a
braces p = do
      symbol "{"
      v <- p
      symbol "}"
      return v

comma :: Parser String
comma = symbol ","

sepBy :: Parser a -> Parser b -> Parser [a]
sepBy p sep = (do
      first <- p
      rest <- many (sep >> p)
      return (first:rest))
      +++ return []

optionMaybe :: Parser a -> Parser (Maybe a)
optionMaybe p = P (\inp ->
      case parse p inp of
            [] -> [(Nothing, inp)]
            [(v, out)] -> [(Just v, out)])


