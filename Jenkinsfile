node {
    def commit_id
    def resultado

    stage('Preparacion'){
        checkout scm
        sh "git rev-parse --short HEAD > .git/commit-id"
        commit_id = readFile('.git/commit-id').trim()
	sh "echo 'WebHook: ${DEV_UXPOS_WEBHOOK}'"
    }

    stage('Compilar'){
	try {
        	def miCompilador = docker.image('conanio/gcc46')
        
        	miCompilador.pull()
        	miCompilador.inside( "-v /tmp/conan/.conan:/home/conan/.conan" ){
            		sh 'conan --version'
        	}

		currentBuild.result = 'SUCCESS'
		resultado = "Se genero una nueva versión de la libreria"
	} catch( Exception err ) {
		currentBuild.result = 'FAILURE'
		resultado = "Se genero un error: ${err}"
	}

	office365ConnectorSend message: "${commit_id}: ${resultado}", status:"${currentBuild.result}", webhookUrl:"${DEV_UXPOS_WEBHOOK}"	
    }
}
