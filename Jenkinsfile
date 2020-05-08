node {
	def commit_id
	def resultado

	stage('Preparacion'){
		checkout scm
		sh "git rev-parse --short HEAD > .git/commit-id"
		commit_id = readFile('.git/commit-id').trim()
		sh "echo 'WebHook: ${DEV_UXPOS_WEBHOOK}'"
	}

	stage('Creacion'){
		try {
			def miCompilador = docker.image('conanio/gcc46')

			miCompilador.pull()
			miCompilador.inside( "-v /tmp/conan/.conan:/home/conan/.conan" ){
				sh 'conan create . uxpos/stable'
			}

			currentBuild.result = 'SUCCESS'
			resultado = "Se ha actualizado la libreria operaciones/0.1.1@uxpos/stable"
		} catch( Exception err ) {
			currentBuild.result = 'FAILURE'
			resultado = "Se ha generado un error: ${err} : al momento de crear la libreria operaciones/0.1.1@uxpos/stable"
			office365ConnectorSend message: "${commit_id}: ${resultado}", status:"${currentBuild.result}", webhookUrl:"${DEV_UXPOS_WEBHOOK}"	
		}
	}

	stage('Pruebas'){
		try {
			def miCompilador = docker.image('conanio/gcc46')

			miCompilador.pull()
			miCompilador.inside( "-v /tmp/conan/.conan:/home/conan/.conan" ){
				sh 'conan create test/ uxpos/testing'
				sh 'conan install TestOperaciones/0.1.1@uxpos/testing'
				sh 'bin/test'
			}

			currentBuild.result = 'SUCCESS'
			resultado = "Se ha actualizado la libreria operaciones/0.1.1@uxpos/stable"
		} catch( Exception err ) {
			currentBuild.result = 'FAILURE'
			resultado = "Se ha generado un error: ${err} : no ha pasado las pruebas unitarias la libreria operaciones/0.1.1@uxpos/stable"
			office365ConnectorSend message: "${commit_id}: ${resultado}", status:"${currentBuild.result}", webhookUrl:"${DEV_UXPOS_WEBHOOK}"	
		}
	}

	stage('Subida a Conan'){
		try {
			def miCompilador = docker.image('conanio/gcc46')

			miCompilador.pull()
			miCompilador.inside( "-v /tmp/conan/.conan:/home/conan/.conan" ){
				sh 'conan upload operaciones/0.1.1@uxpos/stable -r=conan-repo'
			}

			currentBuild.result = 'SUCCESS'
			resultado = "Se ha actualizado la libreria operaciones/0.1.1@uxpos/stable en conan-repo"
		} catch( Exception err ) {
			currentBuild.result = 'FAILURE'
			resultado = "Se ha generado un error: ${err} : al momento de subir libreria operaciones/0.1.1@uxpos/stable a conan-repo"
		}

		office365ConnectorSend message: "${commit_id}: ${resultado}", status:"${currentBuild.result}", webhookUrl:"${DEV_UXPOS_WEBHOOK}"	
	}
}
