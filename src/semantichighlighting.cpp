#include "semantichighlighting.h"

SemanticHighlighting::SemanticHighlighting(QObject *parent)
	: QLanguageServerSemantichighlighting{parent}
{

}

QString SemanticHighlighting::name() const {
	return "Semantichighlighting";
}

void SemanticHighlighting::registerHandlers(QLanguageServer* server,
							  QLanguageServerProtocol* protocol) {

}

void SemanticHighlighting::setupCapabilities(const InitializeParams& clientInfo, InitializeResult& result) {
	result.capabilities.semanticTokensProvider
}
