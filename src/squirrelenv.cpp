#include "squirrelenv.h"

SquirrelEnv::SquirrelEnv()
{
	sq_new(m_state, SQSharedState);
	m_lexer = new SQLexer();
	m_lexer->Init(m_state, );
}
