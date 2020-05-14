pipeline {
	agent {
		docker {
			image 'conanio/gcc7'
			args '-v /tmp/conan/.conan:/home/conan/.conan'
		}
	}

	options {
		skipStagesAfterUnstable() 
	}

	environment {
		COMMIT_ID = ""
		RESULTADO = ""

		VERSION = "0.1.2"
		RELEASE = "develop"
		ARTIFACT = "operaciones"
		USER = "uxpos"
	}

	stages{
		stage('Preparacion') {
			steps {
				script {
					checkout scm
					sh "git rev-parse --short HEAD > .git/commit_id"
					COMMIT_ID = readFile('.git/commit_id').trim()
				}
			}
		}

		stage('Compilacion') {
			steps {
				script {
					try {
						sh "conan create . ${USER}/${RELEASE}"
						RESULTADO = "Se ha compilado localmente la libreria ${ARTIFACT}/${VERSION}@${USER}/${RELEASE}"
					} catch( Exception err ) {
						currentBuild.result = 'FAILURE'
						RESULTADO = "Se ha generado un error: ${err} : al momento de compilar ${ARTIFACT}/${VERSION}@${USER}/${RELEASE}"

						office365ConnectorSend message: "${COMMIT_ID}: ${RESULTADO}", status:"${currentBuild.result}", webhookUrl:"${DEV_UXPOS_WEBHOOK}"
						sh 'exit 1'
					}
				}
			}
		}

		stage('Pruebas') {
			steps {
				script {
					try {
						sh 'conan create src/test/ test${USER}/testing'
						sh 'mkdir build && cd build && conan install test${ARTIFACT}/${VERSION}@{USER}/testing'
						sh 'build/bin/test'
						RESULTADO = "Se han realizado las pruebas unitarias de ${ARTIFACT}/${VERSION}@${USER}/{RELEASE}"
					} catch( Exception err ) {
						currentBuild.result = 'FAILURE'
						RESULTADO = "Se ha generado un error: ${err} : No ha pasado las pruebas unitarias ${ARTIFACT}/${VERSION}@${USER}/${RELEASE}"

						office365ConnectorSend message: "${COMMIT_ID}: ${RESULTADO}", status:"${currentBuild.result}", webhookUrl:"${DEV_UXPOS_WEBHOOK}"
						sh 'exit 1'
					}
				}
			}
		}

		stage('Subida a Repositorio') {
			steps {
				script {
					try {
						sh 'conan upload ${ARTIFACT}/${VERSION}@${USER}/${RELEASE} -r=conan-repo --all'
						RESULTADO = "Se ha actualizado ${ARTIFACT}/${VERSION}@${USER}/${RELEASE} en repositorio conan-repo."
						currentBuild.result = 'SUCCESS'
					} catch( Exception err ) {
						currentBuild.result = 'FAILURE'
						RESULTADO = "Se ha generado un error: ${err} : al momento de subir ${ARTIFACT}/${VERSION}@${USER}/${RELEASE} al repositorio conan-repo."
					}

					office365ConnectorSend message: "${COMMIT_ID}: ${RESULTADO}", status:"${currentBuild.result}", webhookUrl:"${DEV_UXPOS_WEBHOOK}"
				}
			}
		}

		stage('Limpieza') {
			steps {
				script {
					sh 'rm -rf build bin'
					sh 'conan remove "*" -f'
				}
			}
		}
	}
}
