pipeline {
	agent {
		docker {
			image 'conanio/gcc46'
			args '-v /tmp/conan/.conan:/home/conan/.conan'
		}
	}

	environment {
		COMMIT_ID = ""
		RESULTADO = ""
	}

	stages{
		stage('Preparacion') {
			steps {
				checkout scm
				sh "git rev-parse --short HEAD > .git/COMMIT_ID"
				commit_id = readFile('.git/COMMIT_ID').trim()
				sh "echo 'WebHook: ${DEV_UXPOS_WEBHOOK}'"
			}
		}

		stage('Compilacion') {
			steps {
				try {
					sh 'conan create . uxpos/stable'
					RESULTADO = "Se ha compilado localmente la libreria operaciones/0.1.1@uxpos/stable"
				} catch( Exception err ) {
					currentBuild.result = 'FAILURE'
					RESULTADO = "Se ha generado un error: ${err} : al momento de compilar la libreria operaciones/0.1.1@uxpos/stable"

					office365ConnectorSend message: "${commit_id}: ${RESULTADO}", status:"${currentBuild.result}", webhookUrl:"${DEV_UXPOS_WEBHOOK}"
				}
			}
		}

		stage('Pruebas') {
			steps {
				try {
					sh 'conan create src/test/ uxpos/testing'
					sh 'mkdir build && cd build && conan install TestOperaciones/0.1.1@uxpos/testing'
					sh 'build/bin/test'
					RESULTADO = "Se ha actualizado la libreria operaciones/0.1.1@uxpos/stable"
				} catch( Exception err ) {
					currentBuild.result = 'FAILURE'
					RESULTADO = "Se ha generado un error: ${err} : no ha pasado las pruebas unitarias la libreria operaciones/0.1.1@uxpos/stable"

					office365ConnectorSend message: "${commit_id}: ${RESULTADO}", status:"${currentBuild.result}", webhookUrl:"${DEV_UXPOS_WEBHOOK}"
				}
			}
		}

		stage('Subida a Conan') {
			steps {
				try {
					sh 'conan upload operaciones/0.1.1@uxpos/stable -r=conan-repo'
					RESULTADO = "Se ha actualizado la libreria operaciones/0.1.1@uxpos/stable en conan-repo"
					currentBuild.result = 'SUCCESS'
				} catch( Exception err ) {
					currentBuild.result = 'FAILURE'
					RESULTADO = "Se ha generado un error: ${err} : al momento de subir libreria operaciones/0.1.1@uxpos/stable a conan-repo"
				}

				office365ConnectorSend message: "${commit_id}: ${RESULTADO}", status:"${currentBuild.result}", webhookUrl:"${DEV_UXPOS_WEBHOOK}"
			}
		}
	}
}
