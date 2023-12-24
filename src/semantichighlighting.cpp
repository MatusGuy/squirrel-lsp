#include "semantichighlighting.h"

SemanticHighlighting::SemanticHighlighting(QObject *parent)
	: QLanguageServerModule{parent}
{

}

QString SemanticHighlighting::name() const {
	return "SemantichHighlighting";
}

void SemanticHighlighting::registerHandlers(QLanguageServer* server,
							  QLanguageServerProtocol* protocol) {
	protocol->hand
}

void SemanticHighlighting::setupCapabilities(const InitializeParams& clientInfo, InitializeResult& result) {
	result.capabilities.semanticTokensProvider = SemanticTokensOptions{
		true,
		SemanticTokensLegend{
			SEMANTIC_TOKEN_NAMES,
			{}
		},
		false,
		true
	};
}
