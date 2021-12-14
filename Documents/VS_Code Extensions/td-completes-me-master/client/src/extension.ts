'use strict';

import * as vscode from 'vscode';
import * as path from 'path';
import * as fs from 'fs';

import {workspace, Disposable, ExtensionContext} from 'vscode';
import {LanguageClient, LanguageClientOptions, ServerOptions, TransportKind, CodeActionContext } from 'vscode-languageclient';

let client: LanguageClient;
export function activate(context: vscode.ExtensionContext) {

	console.log('Congratulations, your extension "client" is now active!');
	let serverModule = context.asAbsolutePath(path.join('server','out','server.js'));
	let debugOptions = {execArgv : ["--nolazy", "--inspect=6009"]};

	let serverOptions:ServerOptions = {
		run : {module:serverModule, transport:TransportKind.ipc},
		debug : {module:serverModule, transport:TransportKind.ipc, options:debugOptions}
	};

	let clientOptions : LanguageClientOptions = {
		documentSelector : [{scheme:'file', language:'python'}],
		synchronize : {
			fileEvents : workspace.createFileSystemWatcher('**/.clientrc')
		}
	};

	client = new LanguageClient('tdCompletesMe','TD AutoComplete Engine', serverOptions,clientOptions);

	
	client.start();

}

// this method is called when your extension is deactivated
export function deactivate() {
	if (!client) {
		return undefined;
	}
	return client.stop();
}
