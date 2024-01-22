#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Util.h>
#include <iostream>

NGLScene::NGLScene()
{
	// re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
	//setTitle("Blank NGL");
}
NGLScene::NGLScene( QWidget *_parent ) : QOpenGLWidget( _parent )
{

	// set this widget to have the initial keyboard focus
	setFocus();
	// re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
	resize(_parent->size());	
}


NGLScene::~NGLScene()
{
	std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}



void NGLScene::resizeGL(int _w , int _h)
{
	m_win.width  = static_cast<int>( _w * devicePixelRatio() );
	m_win.height = static_cast<int>( _h * devicePixelRatio() );
	m_project = ngl::perspective(45.0f, static_cast<float>(_w)/_h, 0.1f, 100.0f);
}


void NGLScene::initializeGL()
{
	// we must call that first before any other GL commands to load and link the
	// gl commands from the lib, if that is not done program will crash
	ngl::NGLInit::initialize();
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);			   // Grey Background
	// enable depth testing for drawing
	glEnable(GL_DEPTH_TEST);
	// enable multisampling for smoother drawing
	glEnable(GL_MULTISAMPLE);

	

	ngl::ShaderLib::loadShader("ParticleShader", "shaders/ParticleVertex.glsl", "shaders/ParticleFragment.glsl");
	ngl::ShaderLib::use("ParticleShader");
	m_view = ngl::lookAt({0,24,24}, {0,0,0}, {0,1,0});
	ngl::ShaderLib::setUniform("MVP", m_project * m_view);
	startTimer(10);


	m_previousTime = std::chrono::steady_clock::now();
	m_sim = std::make_unique<ClothSim>(-9.81f, ngl::Vec3{ 0.0f, 0.0f, 0.0f }, 800, 10, 20, 20, 40);
}



void NGLScene::paintGL()
{
	// clear the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,m_win.width,m_win.height);
	auto rotX = ngl::Mat4::rotateX(m_win.spinXFace);
	auto rotY = ngl::Mat4::rotateY(m_win.spinYFace);
	auto mouseRotation = rotX * rotY;
	mouseRotation.m_m[3][0] = m_modelPos.m_x;
	mouseRotation.m_m[3][1] = m_modelPos.m_y;
	mouseRotation.m_m[3][2] = m_modelPos.m_z;


	ngl::ShaderLib::use("ParticleShader");
	ngl::ShaderLib::setUniform("MVP", m_project*m_view*mouseRotation);

	m_sim->m_mesh->drawGL();
	//  std::cout<<"drawing\n";

	ngl::ShaderLib::use(ngl::nglColourShader);
	ngl::ShaderLib::setUniform("Colour", 1.0f, 0.0f, 1.0f, 1.0f);
	ngl::ShaderLib::setUniform("MVP", m_project*m_view*mouseRotation);
	//  ngl::VAOPrimitives::draw("floor");
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
	// this method is called every time the main window receives a key event.
	// we then switch on the key value and set the camera in the GLWindow
	switch (_event->key())
	{
	// escape key to quite
	case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
	case Qt::Key_Enter :
		m_win.spinXFace=0;
		m_win.spinYFace=0;
		m_modelPos.set(ngl::Vec3::zero());

		break;
	case Qt::Key_Space :
		std::cout << "space pressed\n";
		if (!m_animate)
		{
			m_animate = true;
		}
		else
		{
			m_animate = false;
		}
	default : break;
	}
	// finally update the GLWindow and re-draw

	update();
}

void NGLScene::timerEvent(QTimerEvent *_event)
{
	auto now = std::chrono::steady_clock::now();
	auto delta = std::chrono::duration<float, std::chrono::seconds::period>(now-m_previousTime).count();
	m_previousTime = now;
	if (m_animate)
	{
		m_sim->runSim(delta);
	}
	update();
}

void NGLScene::playAndPause()
{
	m_animate = !m_animate;
}

void NGLScene::updateParameters(float _gravity, float _windX, float _windY, float _windZ)
{
	m_sim->setGravity(_gravity);
	m_sim->setWind(ngl::Vec3{_windX, _windY, _windZ});
}

void NGLScene::addFixedParticle(const QString &text)
{
	size_t i;
	if (text == "Top Left")
	{
		m_sim->m_mesh->getParticle(0, m_sim->m_mesh->getParticleHeight() - 1).isFixed = true;
		i=0;
	}
	else if (text == "Top Right")
	{
		m_sim->m_mesh->getParticle(m_sim->m_mesh->getParticleWidth() - 1, m_sim->m_mesh->getParticleHeight()-1).isFixed = true;
		i=1;
	}
	else if (text == "Top Middle")
	{
		m_sim->m_mesh->getParticle(int((m_sim->m_mesh->getParticleWidth() - 1)/2), m_sim->m_mesh->getParticleHeight()-1).isFixed = true;
		i=2;
	}
	else if (text == "Bottom Left")
	{
		m_sim->m_mesh->getParticle(0, 0).isFixed = true;
		i=3;
	}
	else if (text == "Bottom Right")
	{
		m_sim->m_mesh->getParticle(m_sim->m_mesh->getParticleWidth() - 1, 0).isFixed = true;
		i=4;
	}
	else if (text == "Bottom Middle")
	{
		m_sim->m_mesh->getParticle(int((m_sim->m_mesh->getParticleWidth() - 1)/2), 0).isFixed = true;
		i=5;
	}

	m_sim->setFixedPoint(i, true);
}

void NGLScene::removeFixedParticle(const QString &text)
{
	size_t i;
	if (text == "Top Left")
	{
		m_sim->m_mesh->getParticle(0, m_sim->m_mesh->getParticleHeight() - 1).isFixed = false;
		i=0;
	}
	else if (text == "Top Right")
	{
		m_sim->m_mesh->getParticle(m_sim->m_mesh->getParticleWidth() - 1, m_sim->m_mesh->getParticleHeight()-1).isFixed = false;
		i=1;
	}
	else if (text == "Top Middle")
	{
		m_sim->m_mesh->getParticle(int((m_sim->m_mesh->getParticleWidth() - 1)/2), m_sim->m_mesh->getParticleHeight()-1).isFixed = false;
		i=2;
	}
	else if (text == "Bottom Left")
	{
		m_sim->m_mesh->getParticle(0, 0).isFixed = false;
		i=3;
	}
	else if (text == "Bottom Right")
	{
		m_sim->m_mesh->getParticle(m_sim->m_mesh->getParticleWidth() - 1, 0).isFixed = false;
		i=4;
	}
	else if (text == "Bottom Middle")
	{
		m_sim->m_mesh->getParticle(int((m_sim->m_mesh->getParticleWidth() - 1)/2), 0).isFixed = false;
		i=5;
	}
	m_sim->setFixedPoint(i, false);
}

void NGLScene::createMesh(float _cWidth, float _cHeight, size_t _pWidth, size_t _pHeight)
{
	m_sim->createNewMesh(_cWidth, _cHeight, _pWidth, _pHeight);
}


