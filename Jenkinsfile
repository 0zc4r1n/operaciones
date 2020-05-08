node {
    def commit_id

    stage('Preparacion'){
        checkout scm
        sh "git rev-parse --short HEAD > .git/commit-id"
        commit_id = readFile('.git/commit-id').trim()
	echo ${DEV_UXPOS_WEBHOOK}
    }

    stage('Compilar'){
        def miCompilador = docker.image('conanio/gcc46')
        
        miCompilador.pull()
        miCompilador.inside( "-v /tmp/conan/.conan:/home/conan/.conan" ){
            sh 'conan --version'
        }
    }
}
